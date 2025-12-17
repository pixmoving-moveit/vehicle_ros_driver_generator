#!/usr/bin/python3
# -*- coding: utf-8 -*-

# 检查dbc文件信号和消息的命名是否都是大坨峰命名法
"""
BO_ 1330 SteerStaFb: 8 VCU
 SG_ ChassisSteerEnSta : 0|1@1+ (1,0) [0|1] ""  ACU
 SG_ ChassisSteerSlopover : 1|1@1+ (1,0) [0|1] ""  ACU
 SG_ ChassisSteerWorkMode : 2|2@1+ (1,0) [0|3] ""  ACU
 SG_ ChassisSteerModeFb : 4|4@1+ (1,0) [0|15] ""  VCU
 SG_ ChassisSteerAngleFb : 8|16@1- (1,0) [-500|500] "deg"  ACU
 SG_ ChassisSteerAngleRearFb : 24|16@1- (1,0) [-500|500] "deg"  ACU
 SG_ ChassisSteerAngleSpeedFb : 40|8@1+ (2,0) [0|500] "deg/s"  ACU
"""

import re
import sys
import yaml
import os

def get_messages_and_signals_from_dbc(dbc_file_path):
    """
    从DBC文件中获取所有消息名称和信号名称。

    :param dbc_file_path: DBC文件的路径
    :return: 包含消息名称和信号名称的字典
    """
    messages_and_signals = {}
    try:
        with open(dbc_file_path, 'r', encoding='utf-8') as file:
            lines = file.readlines()

        current_message = None
        for line in lines:
            # 检查是否是消息定义行
            message_match = re.match(r"^BO_ (\d+) (\S+) *:.*", line)
            if message_match:
                message_id, message_name = message_match.groups()
                current_message = message_name
                messages_and_signals[current_message] = []

            # 检查是否是信号定义行
            signal_match = re.match(r"^ SG_ (\S+) .*", line)
            if signal_match and current_message:
                signal_name = signal_match.group(1)
                messages_and_signals[current_message].append(signal_name)
    except Exception as e:
        print(f"加载DBC文件时出错: {e}, dbc文件编码不是utf-8")
    return messages_and_signals


def check_naming_convention(messages_and_signals):
    """
    检查消息名称和信号名称是否符合大坨峰命名法或包含连续的大写字母。

    :param messages_and_signals: 包含消息名称和信号名称的字典
    :return: 不符合命名规范的消息名称和信号名称列表
    """
    def is_camel_case(name):
        # 检查是否符合大坨峰命名法（以大写字母开头，后续单词以大写开头） 不符合时返回True
        return not bool(re.match(r'^[A-Z][a-zA-Z0-9]*$', name))
    
    def has_consecutive_uppercase(name):
        # 检查是否存在连续3个的大写字母 存在时返回True
        return bool(re.search(r'[A-Z]{3,}', name))

    non_compliant = []

    for message_name, signals in messages_and_signals.items():
        is_check = {"is_camel_case": [False, ''], "has_consecutive_uppercase": [False, '']}
        if is_camel_case(message_name):
            is_check['is_camel_case'][0] = True
            is_check['is_camel_case'][1] = '不符合大坨峰命名法'
        if has_consecutive_uppercase(message_name):
            is_check['has_consecutive_uppercase'][0] = True
            is_check['has_consecutive_uppercase'][1] = '存在连续3个的大写字母'
        
        if is_check['has_consecutive_uppercase'][0] or is_check['is_camel_case'][0]:
            non_compliant.append(f"消息: {message_name} ({is_check['is_camel_case'][1]}, {is_check['has_consecutive_uppercase'][1]})")

        for signal in signals:
            is_check = {"is_camel_case": [False, ''], "has_consecutive_uppercase": [False, '']}
            if is_camel_case(signal):
                is_check['is_camel_case'][0] = True
                is_check['is_camel_case'][1] = '不符合大坨峰命名法'
            if has_consecutive_uppercase(signal):
                is_check['has_consecutive_uppercase'][0] = True
                is_check['has_consecutive_uppercase'][1] = '存在连续3个的大写字母'
            
            if  is_camel_case(signal) or has_consecutive_uppercase(signal):
                non_compliant.append(f"信号: {signal} (属于消息: {message_name}) ({is_check['is_camel_case'][1]}, {is_check['has_consecutive_uppercase'][1]})")
    
    return non_compliant

def check_dbc_naming(dbc_path):
    """判断DBC文件是否命名规范, 不规范时反馈False"""
    # 获取消息和信号
    messages_and_signals = get_messages_and_signals_from_dbc(dbc_path)

    # 检查命名规范
    non_compliant_items = check_naming_convention(messages_and_signals)
    
    # 打印结果
    if non_compliant_items:
        print("以下消息或信号不符合命名规范:")
        for item in non_compliant_items:
            print(item)
        return False
    else:
        print("所有消息和信号都符合命名规范。")
        return True
        
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)

    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)

    dbc_path = os.path.join(conf["config_dir"], conf["dbc_file"])
    check_dbc_naming(dbc_path)

    
    # def is_camel_case(name):
    #     return not bool(re.match(r'^[A-Z][a-zA-Z0-9]*$', name))
    # name  = 'VehicleErrcode1'
    # print(is_camel_case(name))
