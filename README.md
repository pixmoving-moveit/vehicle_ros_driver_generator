# Vehicle ROS Driver Generator
项目基于 Apollo 的 [Gen Vehicle Protocol Tool](https://github.com/ApolloAuto/apollo/tree/master/modules/tools/gen_vehicle_protocol) 改造。

## 处理流程

```text
config/a31.dbc + config/gen_a31.yml
                  |
                  v
extract_dbc_meta.py
  UTF-8 读取 -> 整理 SG_ 冒号空格 -> 原版逐行解析 BO_/SG_
             -> 统一名称、收发分类、关联 CM_/VAL_
             -> 检查名称冲突 -> 写入 YAML
                  |
                  v
config/robobus_a31.yml       (protocol_conf)
                  |
                  v
gen.py 调用后续生成模块
  +-- gen_protocols.py   -> CAN 信号解析/打包代码
  +-- gen_ros_node.py    -> control_command / report_parser
  +-- gen_msg_file.py    -> ROS 消息定义 .msg
  +-- gen_config_file.py -> CMakeLists.txt / package.xml
                  |
                  v
output/src/pix_robobus_driver
output/src/pix_robobus_driver_msgs
```

## extract_dbc_meta.py


| 修改位置 | 原行为 | 当前行为 |
|---|---|---|
| `camel_case_to_snake_case()` | 每个大写字母前插入下划线，缩略词会被拆散，还可能产生重复下划线 | 将连续大写缩略词作为一个词处理，合并重复下划线；例如 `VCU_ChassisDriverEnSta` 转为 `vcu_chassis_driver_en_sta` |
| 文件读取、`extract_var_info()` | 使用系统默认编码，按 `SG_ Name : 0\|8@1+ ...` 的分词位置取值 | 固定 UTF-8 读取，将紧凑格式中的冒号补为空格分隔后复用原解析逻辑；单位文本保留原值 |
| `BO_` / `SG_` 收集 | 依赖后续非信号行将报文加入结果，可能漏掉末尾报文 | 保留原逻辑，补上遇到下一条报文及文件结束时保存上一报文的处理 |
| `CM_ SG_` / `VAL_` 关联 | 用已转换的信号名匹配 DBC 原名，可能丢失注释和枚举 | 引用名称使用相同规则转换后匹配，枚举常量也使用规范化名称；跳过黑名单报文的引用 |
| `protocol_type` 分类 | 发送节点或列表中的报文 ID 匹配为 `control`，列表使用一次性迭代器 | 列表转为集合，支持报文 ID、规范化后的报文名及发送节点匹配；当前配置下 ACU 为 `control`，VCU 为 `report` |
| 名称冲突定位 | 缺少名称冲突检查 | 检查不同报文之间及同一报文内的信号重名；报错列出两个原名和行号，信号冲突还列出所属报文及 CAN ID |
| 保留名称处理 | `minor`、`major`、`long`、`int`、`auto` 加 `MY_` 前缀 | 改为小写 `my_` 前缀，并纳入同一报文内的名称冲突检查 |
| YAML 输出 | 直接打开目标文件写入 | 先完成名称检查及 YAML 序列化，再打开目标文件；中文以 UTF-8 输出 |
| 命令行入口 | 调用缺少版本参数，协议输出路径与 `gen.py` 不一致 | 补齐 `version_major/minor`，统一输出到 `config_dir/protocol_conf`，增加信号总数输出 |

YAML 顶层仍为 `car_type`、`version_major`、`version_minor`、`protocols`，继续供现有生成模块使用。没有引入新的第三方解析库。

信号基础类型沿用原规则：1 位为 `bool`；其余信号若范围文本含小数点或缩放系数不为 1，则为 `double`，否则为 `int`。存在 `VAL_` 时类型改为 `enum`；当前消息生成器将 `enum` 输出为 `int8`、`double` 输出为 `float32`、`int` 输出为 `int32`。因此恢复枚举关联后，部分字段类型会与旧版遗漏枚举时不同。

## DBC 输入要求

使用 gb2312 编码，报文长度为 8 字节；信号定义采用下列固定格式。

```dbc
BO_ 1328 VA_DriveStaFb: 8 VCU
SG_ VCU_ChassisDriverEnSta:0|1@1+ (1,0) [0|1] "" ACU
SG_ VCU_ChassisThrottlePaldFb:24|10@1+ (0.1,0) [0|100] "%" ACU

CM_ SG_ 1328 VCU_ChassisDriverEnSta "驱动使能状态";
VAL_ 1328 VCU_ChassisDriverEnSta 0 "Disable" 1 "Enable";
```

- `Name:bit|length@order/sign` 内部不插入空格；`(factor,offset)`、`[min|max]` 内部也不插入空格，接收节点占一个分词。
- `@1` 为 Intel 字节序，`@0` 为 Motorola 字节序；`+` 表示无符号，`-` 表示有符号。
- 每个报文包含 1～64 个信号，每个信号长度为 1～32 位，且必须位于 8 字节数据范围内。
- `CM_` 和 `VAL_` 放在报文及信号定义之后，单行书写，按示例在结束引号后紧接分号；信号引用应与原始名称一致。
- 不自动识别或转换其他编码，不支持复用信号或超过 8 字节的报文。

解析器处理 `BO_`、`SG_`、信号注释 `CM_ SG_` 和枚举 `VAL_`，其他元数据段不进入协议 YAML。以上是输入约定；最小修补版保留名称冲突定位，不包含此前重写版的完整非法格式、字段越界、数值范围、重复 CAN ID 和未知引用校验，部分不符合原解析规则的定义仍可能被跳过。

名称冲突、读取解析异常或 YAML 序列化失败都发生在打开输出文件之前，因此这些错误不会覆盖已有 YAML。文件写入沿用直接写入方式，不提供此前版本的临时文件原子替换保护。

## 命名规则
<全大写>_<大驼峰命名法>， 例如V2A_DriveStaFb
缩写词命名规范：<全大写>_
非缩写词命名规范：<大驼峰命名法>，例如SafeBeltSta4
开头的`<全大写>_`可以没有
字段名可以带有数字，例如：SafeBeltSta5
V2A_ -> VA_
A2V_ -> AV_
DBC文件格式GB2312
字段枚举命名规范： <大驼峰命名法英文>_<中文>，这个格式是为了方便代码解析
_<中文> 可以没有，用于中文注释
<大驼峰命名法英文> 必须存在，
0 "front ackerman" -> 0 "<FrontAckerman>"
1 "enable(自动驾驶使能驱动控制)" -> 1 "Enable_自动驾驶使能驱动控制"

报文名决定消息文件名、消息类型和话题；信号名决定消息字段。`extract_dbc_meta.py` 先生成小写下划线名称，后续消息生成器再将报文名转换为大驼峰。

| DBC 报文名 | YAML 名称 | 消息文件 / C++ 类型 | C++ 头文件 | 话题 |
|---|---|---|---|---|
| `VA_DriveStaFb` | `va_drive_sta_fb` | `VaDriveStaFb.msg` / `VaDriveStaFb` | `va_drive_sta_fb.hpp` | `/pix_robobus/va_drive_sta_fb` |
| `VCU_SoftVer` | `vcu_soft_ver` | `VcuSoftVer.msg` / `VcuSoftVer` | `vcu_soft_ver.hpp` | `/pix_robobus/vcu_soft_ver` |

| DBC 信号名 | YAML / 消息字段名 |
|---|---|
| `VCU_ChassisDriverEnSta` | `vcu_chassis_driver_en_sta` |
| `VCU_ChassisThrottlePaldFb` | `vcu_chassis_throttle_pald_fb` |
| `VCU_ChassisBrakePadlFb` | `vcu_chassis_brake_padl_fb` |

这里的字段和话题采用小写下划线命名（snake_case），消息类型采用大驼峰（PascalCase）。名称转换不会猜测缩写含义或纠正拼写：`Pald`、`Padl` 已在 DBC 中明确保留，其他信号里的 `Pedal` 继续使用其原名。

不同报文规范化后重名，或同一报文中的信号规范化后重名，都会报错。例如 `VCU_State` 与 `VcuState` 都变成 `vcu_state` 时，需要人工修改 DBC 原名，不自动添加序号。

修改 DBC 信号名时，也要同步修改引用该信号的 `CM_ SG_`、`VAL_`。重新生成后，调用方使用的类型、字段和话题应与生成结果一致。

## 配置与运行

生成阶段使用 Python 3 和 PyYAML。从项目根目录运行命令，使配置中的相对路径和模板路径正确解析。

当前 `config/gen_a31.yml`：

```yaml
dbc_file: a31.dbc
protocol_conf: robobus_a31.yml
car_type: robobus
sender_list: []
sender: ACU
black_list: []
version_major: 3
version_minor: 1
output_dir: output/src
config_dir: config
```

`sender_list: []` 时按发送节点分类：发送节点为 ACU 的报文是 `control`，其余是 `report`。当前 A31 其余发送节点均为 VCU。需要显式指定时，`sender_list` 可填写报文名或小写十六进制 ID 字符串；`black_list` 使用相同形式的 ID 字符串，不带 `0x`，例如 `"530"`。

仅生成协议 YAML：

```bash
python3 extract_dbc_meta.py config/gen_a31.yml
```

输出为 `config/robobus_a31.yml`。`protocol_conf` 位于 `config_dir` 下；`output_dir` 用于后续生成的 ROS 包。

生成协议 YAML、驱动源码及消息包：

```bash
python3 gen.py config/gen_a31.yml
```

该命令会重新生成两个输出包中的对应文件；调用方包中的业务代码需要单独同步。生成源码不会执行 ROS 编译，也不会更新 `build/`、`install/` 中已有的编译产物。


