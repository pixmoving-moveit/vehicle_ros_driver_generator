#!/usr/bin/env python3
"""只读检查无 BOM 的 UTF-8 DBC 命名约定、格式、引用和协议结构。Python 3.9+，首次自动准备依赖。"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
from dataclasses import asdict, dataclass
from importlib import metadata
import json
import os
from pathlib import Path
import platform
import re
import subprocess
import sys

VERSION = '1.1.2'
# 依赖清单内置；Python 3.9 使用仍支持该版本的解析器。
DEPENDENCIES_39 = ('cantools==40.7.1', 'textparser==0.24.0')
DEPENDENCIES_CURRENT = ('cantools==44.2.1', 'textparser==0.26.2')
# 此清单用于发现已知缩写漏写下划线，不限制合法的新前缀。
DEFAULT_PREFIXES = set('AC ACU AD ADCU AV AVAS BCM BMS DCDC DCU DP EHB EPS FLM FLMC FR FRM FRMC '
                       'HAC HAVAS HBCM HBMS HDCDC HDCU HDP HFLM HFLMC HFR HFRM HFRMC HIIS HIV '
                       'HLIS HOBC HRCU HRLM HRLMC HRR HRRM HRRMC IIS LV MCU OBC PDU PWM RCU '
                       'RLM RLMC RR RRM RRMC VA VCU VIN'.split())
QUOTE = re.compile(r'"(?:[^"\\]|\\.)*"', re.DOTALL)
BO = re.compile(r'^[ \t]*BO_\s+(\d+)\s+(\w+)\s*:')
SG = re.compile(r'^[ \t]*SG_\s+(\w+)(?:\s+(M|m\d+M?))?\s*:')
CHINESE = re.compile(r'[\u3400-\u4dbf\u4e00-\u9fff]')
REFERENCE_PATTERNS = [
    re.compile(r'^[ \t]*(?:CM_\s+SG_|VAL_|SIG_VALTYPE_|SG_MUL_VAL_)\s+(\d+)\s+(\w+)(?=\s|:)', re.MULTILINE),
    re.compile(r'^[ \t]*BA_\s+"[^"\\]*"\s+SG_\s+(\d+)\s+(\w+)(?=\s|;)', re.MULTILINE),
]


def dependency_spec():
    return DEPENDENCIES_39 if sys.version_info[:2] == (3, 9) else DEPENDENCIES_CURRENT


def dependencies_ready(requirements):
    try:
        for requirement in requirements:
            name, version = requirement.split('==')
            if metadata.version(name) != version:
                return False
        import cantools.database  # noqa: F401
        return True
    except (ImportError, metadata.PackageNotFoundError):
        return False


def dependency_environment(requirements):
    if sys.platform == 'darwin':
        cache = Path.home() / 'Library' / 'Caches'
    elif os.name == 'nt':
        cache = Path(os.environ.get('LOCALAPPDATA') or (Path.home() / 'AppData' / 'Local'))
    else:
        cache = Path(os.environ.get('XDG_CACHE_HOME') or (Path.home() / '.cache'))
    tag = f'py{sys.version_info.major}.{sys.version_info.minor}-{platform.machine()}-'
    tag += '-'.join(requirements).replace('==', '-')
    return cache / 'dbc-checker' / tag


def cached_dependencies_ready(python, requirements):
    if not python.is_file():
        return False
    probe = ('from importlib.metadata import version; '
             f'assert all(version(r.split("==")[0]) == r.split("==")[1] for r in {requirements!r}); '
             'import cantools.database')
    try:
        result = subprocess.run([str(python), '-I', '-c', probe], capture_output=True, timeout=30)
        return result.returncode == 0
    except (OSError, subprocess.TimeoutExpired):
        return False


def prepare_dependencies(argv, allow_install=True):
    """只向用户缓存中的专用虚拟环境安装；子进程沿用原参数和工作目录。"""
    if sys.version_info < (3, 9):
        print('需要 Python 3.9 或更新版本。', file=sys.stderr)
        return 2
    requirements = dependency_spec()
    if dependencies_ready(requirements):
        return None
    environment = dependency_environment(requirements)
    python = environment / ('Scripts/python.exe' if os.name == 'nt' else 'bin/python')
    try:
        if not cached_dependencies_ready(python, requirements):
            if not allow_install:
                print('尚无可用依赖缓存；请联网后去掉 --no-install 再运行一次。', file=sys.stderr)
                return 2
            print(f'首次运行，正在准备独立依赖环境：{environment}', file=sys.stderr, flush=True)
            environment.parent.mkdir(parents=True, exist_ok=True)
            if not python.is_file():
                subprocess.run([sys.executable, '-m', 'venv', str(environment)], check=True,
                               stdout=sys.stderr, stderr=sys.stderr)
            subprocess.run([str(python), '-I', '-m', 'pip', 'install', '--disable-pip-version-check',
                            '--no-input', *requirements], check=True, stdout=sys.stderr, stderr=sys.stderr)
            if not cached_dependencies_ready(python, requirements):
                print('依赖安装后验证失败；请保留上面的错误输出。', file=sys.stderr)
                return 2
        child_args = list(argv)
        if '--no-install' not in child_args:
            child_args.insert(0, '--no-install')
        return subprocess.run([str(python), '-I', str(Path(__file__).resolve()), *child_args]).returncode
    except (OSError, subprocess.CalledProcessError) as exc:
        print(f'依赖环境准备失败：{exc}\n请检查网络或 Python 的 venv/pip 是否可用，再运行同一命令。', file=sys.stderr)
        return 2


@dataclass
class Issue:
    severity: str
    code: str
    line: int
    message: str


def issue(issues, code, line, message, severity='error'):
    issues.append(Issue(severity, code, line, message))


def check_name(name, line, issues, prefixes):
    """不得先转大小写，否则会掩盖待查文件的错误。"""
    if '_' in name:
        match = re.fullmatch(r'([A-Z][A-Z0-9]*)_([A-Z0-9][A-Za-z0-9]*)', name)
        if not match:
            issue(issues, 'NAME_FORMAT', line,
                  f'{name}：只允许开头一个全大写缩写前缀和下划线，后续为大驼峰且不能再含下划线。')
            return
        prefix, body = match.groups()
        if prefix in ('V2A', 'A2V'):
            issue(issues, 'DIRECTION_PREFIX', line,
                  f'{name}：约定要求 {prefix}_ 改为 {"VA" if prefix == "V2A" else "AV"}_。')
    else:
        body = name
        if not re.fullmatch(r'[A-Z][A-Za-z0-9]*', body):
            issue(issues, 'NAME_FORMAT', line, f'{name}：无缩写前缀时必须以大写英文字母开头，仅含英文字母和数字。')
        for prefix in sorted(prefixes, key=lambda p: (-len(p), p)):
            if name[:len(prefix)].upper() != prefix or len(name) <= len(prefix):
                continue
            tail = name[len(prefix):]
            # ActiveMode 中的 Ac 是普通单词的一部分，不能当作 AC 缩写。
            if tail[0].isupper() or tail[0].isdigit() or name.startswith(prefix):
                issue(issues, 'MISSING_PREFIX_SEPARATOR', line,
                      f'{name}：识别到开头缩写 {prefix}，应使用 {prefix}_ 后接大驼峰。')
                break
    capitals = re.search(r'[A-Z]{2,}', body)
    if capitals:
        issue(issues, 'CONSECUTIVE_CAPITALS', line,
              f'{name}：去掉开头缩写前缀后，仍有连续大写字母“{capitals[0]}”。')


def check_enum(label, line, issues):
    english, sep, chinese = label.partition('_')
    if not re.fullmatch(r'[A-Z][A-Za-z0-9]*', english):
        issue(issues, 'ENUM_FORMAT', line, f'枚举 {label!r}：英文必须存在并使用大驼峰，仅含英文字母和数字。')
    capitals = re.search(r'[A-Z]{2,}', english)
    if capitals:
        issue(issues, 'ENUM_CAPITALS', line, f'枚举 {label!r}：英文部分含连续大写字母“{capitals[0]}”。')
    if sep and not CHINESE.search(chinese):
        issue(issues, 'ENUM_SUFFIX', line, f'枚举 {label!r}：下划线后应为可选中文说明；英文单词不能用下划线分隔。')


def mask_strings(text):
    """保留字符串的边界和行号；多行注释内部不再被识别成 DBC 记录。"""
    def mask(match):
        return '"' + re.sub(r'[^\r\n]', ' ', match[0][1:-1]) + '"'
    return QUOTE.sub(mask, text)


def read_input(path, encoding, issues):
    try:
        raw = path.read_bytes()
    except OSError as exc:
        issue(issues, 'FILE_READ', 0, f'无法读取文件：{exc}')
        return None
    if raw.startswith((b'\xef\xbb\xbf', b'\xff\xfe', b'\xfe\xff')):
        issue(issues, 'ENCODING_BOM', 1, '文件含 BOM；请保存为不带 BOM 的 UTF-8。')
        return None
    try:
        text = raw.decode(encoding, errors='strict')
    except UnicodeDecodeError as exc:
        issue(issues, 'ENCODING', 0,
              f'不能按 {encoding} 严格解码（字节位置 {exc.start}）；请先将文件转换为 UTF-8 编码。')
        return None
    return text


def inspect_text(text, issues, prefixes):
    masked = mask_strings(text)
    masked_lines, original_lines = masked.splitlines(), text.splitlines()
    messages, signal_lines = {}, {}
    signal_counts = Counter()
    references, message_refs = [], []
    current = None
    for lineno, (line, original) in enumerate(zip(masked_lines, original_lines), 1):
        message = BO.match(line)
        if message:
            current, name = int(message[1]), message[2]
            if current in messages:
                issue(issues, 'DUPLICATE_MESSAGE_ID', lineno,
                      f'报文 ID {current} 重复；首次在第 {messages[current][1]} 行。')
            messages[current] = (name, lineno)
            check_name(name, lineno, issues, prefixes)
        signal = SG.match(line)
        if signal:
            name = signal[1]
            key = current, name
            signal_counts[key] += 1
            if key in signal_lines:
                issue(issues, 'DUPLICATE_SIGNAL_NAME', lineno,
                      f'报文 {current} 的信号 {name} 重名；首次在第 {signal_lines[key]} 行。')
            signal_lines.setdefault(key, lineno)
            if current is None:
                issue(issues, 'SIGNAL_WITHOUT_MESSAGE', lineno, f'{name} 没有所属 BO_ 报文。')
            check_name(name, lineno, issues, prefixes)
            if original.startswith((' ', '\t')):
                issue(issues, 'SG_INDENT', lineno, 'SG_ 行首不应有缩进空格或制表符。')
            colon = signal.end() - 1
            if original[colon - 1].isspace() or (colon + 1 < len(original) and original[colon + 1].isspace()):
                issue(issues, 'SG_COLON_SPACE', lineno, f'{name}：冒号两侧应无空格，例如 SG_ {name}:0|8@1+ ...。')
            units = list(QUOTE.finditer(original))
            if len(units) == 1:
                tail = original[units[0].end():]
                gap = re.match(r'([ \t]*)(\S.*)', tail)
                if gap is None or gap[1] != '  ':
                    issue(issues, 'SG_RECEIVER_SPACE', lineno,
                          f'{name}：单位结束引号与接收节点之间必须恰好两个 ASCII 空格。')
    for pattern in REFERENCE_PATTERNS:
        for reference in pattern.finditer(masked):
            lineno = text.count('\n', 0, reference.start()) + 1
            references.append((lineno, int(reference[1]), reference[2]))
    for mux in re.finditer(r'^[ \t]*SG_MUL_VAL_\s+(\d+)\s+\w+\s+(\w+)', masked, re.MULTILINE):
        references.append((text.count('\n', 0, mux.start()) + 1, int(mux[1]), mux[2]))
    message_patterns = [r'^[ \t]*(?:CM_\s+BO_|BO_TX_BU_)\s+(\d+)',
                        r'^[ \t]*BA_\s+"[^"\\]*"\s+BO_\s+(\d+)']
    for pattern in message_patterns:
        for reference in re.finditer(pattern, masked, re.MULTILINE):
            message_refs.append((text.count('\n', 0, reference.start()) + 1, int(reference[1])))
    for group in re.finditer(r'^[ \t]*SIG_GROUP_\s+(\d+)\s+\w+\s+\d+\s*:\s*([^;]*);', masked, re.MULTILINE):
        lineno = text.count('\n', 0, group.start()) + 1
        for name in group[2].split():
            references.append((lineno, int(group[1]), name))
    for lineno, mid, name in references:
        if (mid, name) not in signal_lines:
            issue(issues, 'UNRESOLVED_SIGNAL_REFERENCE', lineno, f'引用 {mid} {name} 找不到同名信号定义。')
    for lineno, mid in message_refs:
        if mid not in messages:
            issue(issues, 'UNRESOLVED_MESSAGE_REFERENCE', lineno, f'引用的报文 ID {mid} 不存在。')
    message_names = defaultdict(list)
    for mid, (name, lineno) in messages.items():
        message_names[name].append(lineno)
    for name, locations in message_names.items():
        if len(locations) > 1:
            issue(issues, 'DUPLICATE_MESSAGE_NAME', locations[-1], f'报文名 {name} 重复，所在行：{locations}。')

    # 在屏蔽字符串后的文本上寻找记录起点，支持多行 VAL_。
    enum_records, enum_items = {}, 0
    for match in re.finditer(r'^[ \t]*VAL_\s+(\d+)\s+(\w+)\s+([^;]*);', masked, re.MULTILINE):
        mid, name = int(match[1]), match[2]
        lineno = text.count('\n', 0, match.start()) + 1
        if (mid, name) in enum_records:
            issue(issues, 'DUPLICATE_ENUM_RECORD', lineno, f'{mid} {name} 有多条 VAL_ 定义。')
        enum_records[mid, name] = lineno
        record = text[match.start():match.end()]
        seen = set()
        for pair in re.finditer(r'(-?\d+)\s+("(?:[^"\\]|\\.)*")', record, re.DOTALL):
            value = int(pair[1])
            value_line = lineno + record.count('\n', 0, pair.start())
            if value in seen:
                issue(issues, 'DUPLICATE_ENUM_VALUE', value_line, f'{name} 的枚举数值 {value} 重复。')
            seen.add(value)
            enum_items += 1
            check_enum(pair[2][1:-1], value_line, issues)
    return messages, signal_lines, sum(signal_counts.values()), enum_items


def load_database(text, issues, label='待查文件'):
    import cantools
    try:
        return cantools.database.load_string(text, 'dbc', strict=True, sort_signals=None)
    except (ValueError, KeyError, TypeError, cantools.database.Error) as exc:
        detail = str(exc)
        line = re.search(r'line (\d+)', detail)
        issue(issues, 'DBC_PARSE', int(line[1]) if line else 0, f'{label}严格解析失败：{detail}')
        return None


def check_ranges(db, signal_lines, issues):
    for message in db.messages:
        # DBC 编码使用最高位标记扩展帧。
        mid = message.frame_id | (0x80000000 if message.is_extended_frame else 0)
        for signal in message.signals:
            if signal.is_float:
                continue
            low = -(1 << (signal.length - 1)) if signal.is_signed else 0
            high = (1 << (signal.length - int(signal.is_signed))) - 1
            minimum, maximum = sorted((low * signal.scale + signal.offset, high * signal.scale + signal.offset))
            if ((signal.minimum is not None and signal.minimum < minimum - 1e-8)
                    or (signal.maximum is not None and signal.maximum > maximum + 1e-8)):
                issue(issues, 'VALUE_RANGE', signal_lines.get((mid, signal.name), 0),
                      f'{signal.name}：声明范围 [{signal.minimum}, {signal.maximum}] 超出位宽可表达的 [{minimum}, {maximum}]；需人工核对。',
                      'warning')


def normalized_label(label):
    return ''.join(c for c in str(label) if c.isalnum()).casefold()


def labels_equivalent(old, new):
    old, new = str(old), str(new)
    if normalized_label(old) == normalized_label(new):
        return True
    if old.casefold() == '4wd' and new == 'FourWd':
        return True
    # 纯中文枚举按约定添加英文；这里只核对中文原文，不能判断翻译对错。
    if CHINESE.search(old) and not re.search(r'[A-Za-z]', old):
        english, sep, chinese = new.partition('_')
        return bool(sep and re.fullmatch(r'[A-Z][A-Za-z0-9]*', english) and chinese == old)
    return False


def dbc_attributes(obj):
    return {name: attr.value for name, attr in getattr(getattr(obj, 'dbc', None), 'attributes', {}).items()}


def compare_baseline(db, original, message_lines, signal_lines, issues):
    """按报文 ID 和位布局配对，允许名称按约定变化，不允许协议内容丢失。"""
    old_messages = {(m.frame_id, m.is_extended_frame): m for m in original.messages}
    new_messages = {(m.frame_id, m.is_extended_frame): m for m in db.messages}
    if [n.name for n in original.nodes] != [n.name for n in db.nodes]:
        issue(issues, 'BASELINE_NODES', 0, '节点列表相对原文件发生变化。')
    for key in sorted(old_messages.keys() | new_messages.keys()):
        mid = key[0] | (0x80000000 if key[1] else 0)
        lineno = message_lines.get(mid, ('', 0))[1]
        if key not in old_messages or key not in new_messages:
            issue(issues, 'BASELINE_MESSAGE', lineno, f'报文 {mid} 相对原文件新增或删除。')
            continue
        old, new = old_messages[key], new_messages[key]
        for attr in ('length', 'senders', 'cycle_time', 'comments', 'is_fd'):
            if getattr(old, attr) != getattr(new, attr):
                issue(issues, 'BASELINE_MESSAGE_CONTENT', lineno, f'报文 {mid} 的 {attr} 相对原文件改变。')
        if dbc_attributes(old) != dbc_attributes(new):
            issue(issues, 'BASELINE_ATTRIBUTES', lineno, f'报文 {mid} 属性值改变。')
        def signal_key(s):
            return s.start, s.length, s.byte_order, tuple(s.multiplexer_ids or ())
        old_signals, new_signals = {}, {}
        for collection, signals in ((old_signals, old.signals), (new_signals, new.signals)):
            for signal in signals:
                skey = signal_key(signal)
                if skey in collection:
                    issue(issues, 'BASELINE_AMBIGUOUS', lineno, f'报文 {mid} 存在无法唯一配对的信号布局，需人工对照。')
                collection[skey] = signal
        for skey in old_signals.keys() | new_signals.keys():
            if skey not in old_signals or skey not in new_signals:
                issue(issues, 'BASELINE_SIGNAL_LAYOUT', lineno, f'报文 {mid} 位 {skey[0]} 的信号新增、删除或位布局改变。')
                continue
            a, b = old_signals[skey], new_signals[skey]
            signal_line = signal_lines.get((mid, b.name), lineno)
            for attr in ('is_signed', 'is_float', 'scale', 'offset', 'minimum', 'maximum', 'unit',
                         'receivers', 'comments', 'initial', 'invalid', 'is_multiplexer'):
                if getattr(a, attr) != getattr(b, attr):
                    issue(issues, 'BASELINE_SIGNAL_CONTENT', signal_line,
                          f'{b.name} 的 {attr} 相对原文件改变。')
            def mux_key(s, message):
                if s.multiplexer_signal is None:
                    return None
                return signal_key(message.get_signal_by_name(s.multiplexer_signal))
            if mux_key(a, old) != mux_key(b, new):
                issue(issues, 'BASELINE_MULTIPLEXER', signal_line, f'{b.name} 的多路复用关系改变。')
            if dbc_attributes(a) != dbc_attributes(b):
                issue(issues, 'BASELINE_ATTRIBUTES', signal_line, f'{b.name} 的属性值改变。')
            old_choices, new_choices = a.choices or {}, b.choices or {}
            if list(old_choices) != list(new_choices):
                issue(issues, 'BASELINE_ENUM_VALUES', signal_line, f'{b.name} 的枚举数值或顺序相对原文件改变。')
            for value in old_choices.keys() & new_choices.keys():
                if not labels_equivalent(old_choices[value], new_choices[value]):
                    issue(issues, 'BASELINE_ENUM_TEXT', signal_line,
                          f'{b.name} 枚举 {value} 的文本超出大小写/分隔格式调整：{str(old_choices[value])!r} → {str(new_choices[value])!r}。')


def check_file(path, encoding, prefixes, baseline=None, baseline_encoding=None):
    issues = []
    text = read_input(path, encoding, issues)
    messages, signals, enum_items = 0, 0, 0
    if text is not None:
        message_lines, signal_lines, signals, enum_items = inspect_text(text, issues, prefixes)
        messages = len(message_lines)
        db = load_database(text, issues)
        if db is not None:
            check_ranges(db, signal_lines, issues)
        if baseline is not None:
            baseline_issues = []
            base_text = read_input(baseline, baseline_encoding or encoding, baseline_issues)
            for item in baseline_issues:
                issue(issues, 'BASELINE_' + item.code, 0, f'原文件 {baseline}：{item.message}')
            if base_text is not None:
                original = load_database(base_text, issues, f'原文件 {baseline}')
                if db is not None and original is not None:
                    compare_baseline(db, original, message_lines, signal_lines, issues)
    issues.sort(key=lambda i: (i.line, i.severity, i.code))
    return dict(file=str(path), encoding=encoding, decoded=text is not None,
                messages=messages, signals=signals, enum_items=enum_items,
                errors=sum(i.severity == 'error' for i in issues), warnings=sum(i.severity == 'warning' for i in issues),
                issues=[asdict(i) for i in issues])


def main(argv=None):
    argv = sys.argv[1:] if argv is None else list(argv)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('files', nargs='+', type=Path, help='待检查的 DBC 文件，可同时检查多份')
    parser.add_argument('--encoding', choices=['utf-8'], default='utf-8',
                        help='固定使用 UTF-8，文件不能带 BOM')
    parser.add_argument('--prefix', action='append', default=[], help='补充已知缩写，例如 --prefix XYZ；不含下划线，可重复')
    parser.add_argument('--baseline', type=Path, help='可选原始 DBC，核对是否新增、删除或改变协议内容；仅适用于一个待查文件')
    parser.add_argument('--baseline-encoding', choices=['utf-8'], help='原文件也必须使用无 BOM 的 UTF-8，默认与待查文件相同')
    parser.add_argument('--json', type=Path, help='另存 JSON 检查报告；不能覆盖输入文件')
    parser.add_argument('--no-install', action='store_true', help='禁止下载安装依赖；可复用已准备好的本地缓存')
    parser.add_argument('--version', action='version', version=VERSION)
    args = parser.parse_args(argv)
    if args.baseline and len(args.files) != 1:
        parser.error('--baseline 只能与一个待查文件一起使用。')
    for prefix in args.prefix:
        if not re.fullmatch(r'[A-Z][A-Z0-9]*', prefix):
            parser.error('--prefix 必须为全大写缩写，可含数字，不含下划线。')
    protected = args.files + ([args.baseline] if args.baseline else [])
    if args.json:
        for source in protected:
            same_path = args.json.resolve() == source.resolve()
            try:
                same_file = args.json.exists() and source.exists() and args.json.samefile(source)
            except OSError:
                same_file = False
            if same_path or same_file:
                parser.error('--json 不能与待查文件或原文件指向同一个文件。')
    dependency_result = prepare_dependencies(argv, allow_install=not args.no_install)
    if dependency_result is not None:
        return dependency_result
    results = [check_file(p, args.encoding, DEFAULT_PREFIXES | set(args.prefix), args.baseline, args.baseline_encoding)
               for p in args.files]
    for result in results:
        inventory = (f'{result["messages"]} 条报文，{result["signals"]} 个信号'
                     if result['decoded'] else '未解析报文和信号（文件读取或编码错误）')
        print(f'\n{result["file"]}：{inventory}，'
              f'{result["errors"]} 个错误，{result["warnings"]} 个提示')
        for item in result['issues']:
            severity = '错误' if item['severity'] == 'error' else '提示'
            location = f'第 {item["line"]} 行' if item['line'] else '文件级'
            print(f'  {location} [{severity}/{item["code"]}] {item["message"]}')
        if result['errors'] == 0:
            print('  检查通过' + ('（有需人工核对的提示）' if result['warnings'] else ''))
    if args.json:
        try:
            args.json.write_text(json.dumps(dict(checker_version=VERSION, files=results), ensure_ascii=False, indent=2) + '\n', encoding='utf-8')
        except OSError as exc:
            print(f'无法写入报告：{exc}', file=sys.stderr)
            return 2
    return 1 if any(r['errors'] for r in results) else 0


if __name__ == '__main__':
    sys.exit(main())
