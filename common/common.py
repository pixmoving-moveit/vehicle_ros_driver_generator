#!/usr/bin/env python3
# -*- coding: utf-8 -*-
def get_tpl_fmt(tpl_file):
    """获取模版文件str

    Args:
        tpl_file (str): 模版文件地址

    Returns:
        str: 模版文件的str
    """
    with open(tpl_file, 'r') as tpl:
        fmt = tpl.readlines()
    fmt = "".join(fmt)
    return fmt

def get_name_info(protocols:dict):
    # message名称 + CAN-ID = va_vcu_sofver_0x10f
    # infoList 引用列表
    message_name_list = {}
    message_name_list["report"] = list()
    message_name_list["control"] = list()
    for protocol in protocols.values():
        if protocol["protocol_type"] == "report":
            message_name_list["report"].append(f"{protocol['name']}")
        elif protocol["protocol_type"] == "control":
            message_name_list["control"].append(f"{protocol['name']}")
        else:
            print("Unknown protocol_type:%s" % protocol["protocol_type"])
            
    return message_name_list

    
def gen_esd_can_extended(str):
    # canID 大于 0x800时[与或]处理
    """
        id string:
    """
    int_id = int(str, 16)
    int_id &= 0x1FFFFFFF
    int_id |= 0x20000000
    str = hex(int_id).replace('0x', '')
    return str

def get_byte_info(var):
    """
        doc string: https://wenku.baidu.com/view/3fe9a7a4dd3383c4bb4cd293.html
        u can reference this link to known the difference between motorola and intel encoding
        return : the byte info of a variable in the protocol how many bytes are, and every byte use
                 how many bits, and bit start position
                 for the purpose of easily parsing value from CAN frame, the byte_info is arranged
                 from msb byte to lsb byte order
    """
    bit = var["bit"]
    byte_info = []
    left_len = var["len"]
    byte_idx = bit // 8
    bit_start = bit % 8
    if var["order"] == "motorola":
        while left_len > 0:
            info = {}
            info["byte"] = byte_idx
            info["len"] = min(bit_start + 1, left_len)
            # start_bit is always the lowest bit
            info["start_bit"] = bit_start - info["len"] + 1
            byte_info.append(info)
            left_len = left_len - info["len"]
            byte_idx = byte_idx + 1
            bit_start = 7
    else:
        while left_len > 0:
            info = {}
            info["byte"] = byte_idx
            info["len"] = min(8 - bit_start, left_len)
            info["start_bit"] = bit_start
            byte_info.append(info)
            left_len = left_len - info["len"]
            byte_idx = byte_idx + 1
            bit_start = 0
        # byte_info is always construct with msb(most significant bit) byte to lsb byte
        byte_info.reverse()
    return byte_info

