#!/usr/bin/python3
import cantools
import chardet
import re
import sys
import os


if len(sys.argv) < 2:
    print( "usage: dbc_naming_conventions.py [your_dbc_file]")
    exit(1)

source_dbc_file = sys.argv[1]
# source_dbc_file = "/home/dept/zymouse/workspace/dbc_naming_conventions/vehicle_ros_driver_generator/source.dbc"
if not os.path.exists(source_dbc_file):
    print(f"'{source_dbc_file}' File does not exist.")
    exit(1)


with open(source_dbc_file, "rb") as file:
    file_content = file.read()
    detected_encoding = chardet.detect(file_content)['encoding']
    utf8_text = file_content.decode(detected_encoding, 'ignore')
    db = cantools.database.load_string(utf8_text)

BU_ = '|'.join([node.name for node in db.nodes])

def pascal_case(text):
    # 下划线分词
    parts = text.split('_')
    # BCMPowVCUTubeMos1
    for index in range(len(parts)):
        part = parts[index]
        if part in BU_:
            continue
        found_words = re.findall(BU_, part)
        for found_word in found_words:
            found_words = found_words[1:]
            start_position = part.find(found_word)
            end_position = start_position+len(found_word)
            if(start_position==0):
                part = part[start_position:end_position] +'_'+ part[end_position:]
            else:
                part = part[:start_position] +'_'+ part[start_position:end_position] +'_'+ part[end_position:]
            parts[index] = part

    parts_fix = []
    for index in range(len(parts)):
        part = parts[index]
        if(part.find('_')):
            part = part.split('_')
            parts_fix = parts_fix+part
        else:
            parts_fix.append(part)

    parts = parts_fix

    # 单词全大写时-变大驼峰
    for i in range(len(parts)):
        if re.match(r'^[A-Z0-9]+$', parts[i]):
            parts[i]=parts[i].lower().capitalize()
    
    # 单词全小写时-变大驼峰
    for i in range(len(parts)):
        if re.match(r'^[a-z0-9]+$', parts[i]):
            parts[i]=parts[i].lower().capitalize()
    # 按首字母大写分词
    words = []
    for part in parts:
        words.extend(re.findall('[A-Z][a-z0-9]*', part))    
    
    return ''.join(word.lower().capitalize() for word in words)


# pascal_case("BCM_Message1BCMPowIMUTubeMos1")
# example_message = db.get_message_by_name('OBC_BMS_Sta2')
# pprint(example_message.signals)
# pprint(db.nodes[0].name)

# 遍历所有信号并规范化名称
for message in db.messages:
    message.name = pascal_case(message.name)  # 规范化消息名称
    for signal in message.signals:
        a = pascal_case(signal.name)  # 规范化信号名称
        signal.name = a

base_name, file_extension = os.path.splitext(source_dbc_file)
output_dbc_file = source_dbc_file + '_standardize' + file_extension
cantools.database.dump_file(db, output_dbc_file, encoding='utf-8', sort_signals=lambda signals: list(sorted(signals, key=lambda sig: sig.start)) )


