#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import  yaml
import sys
import os
import re

def snake_case_to_camel_case(snake_str):
    return "".join(x.capitalize() for x in snake_str.lower().split("_"))

def to_lower_case(var_name):
    lower_case_name = ''
    for i, c in enumerate(var_name):
        if c.isupper() and i > 0 and var_name[i-1] != '_':
            lower_case_name += '_' + c.lower()
        else:
            lower_case_name += c.lower()
    return lower_case_name


def write_single_protocol_vars(pb_fp, p):
    """
    解析yaml文件,往msg文件填入信息
    params: 
        pb_fp: 需要填写内容的文件对象
        p:    yaml对象,帧ID的详细信息
    """
    for var in p["vars"]:
        # # 过滤-相等的物理最值
        # if minnum != maxnum:
        if "description" in var:
            notes = "# %s [%s] %s\n"%(var["description"], var["physical_unit"], var["physical_range"])
            pb_fp.write(notes)
        else:
            notes = "# %s [%s] %s\n"%("", var["physical_unit"], var["physical_range"])
            pb_fp.write(notes)
        # 填入msg 定义
        t = var["type"]
        if t == "int":
            t = "int32"
        elif t== "enum":
            t = "int8"
        elif t== "double":
            t = "float32"
        fmt = "%s %s \n"
        pb_fp.write(fmt%(t, var["name"]))
        

def gen_proto_file(config_file, work_dir):
    """
    解析的yaml文件,迭代生成msg文件,同时填入该帧的信号信息
    param: 
        config_file : yaml解析文件路径
        work_dir  : msg生成文件存储路径
    """
    # 读取DBC解析的yaml文件
    with open(config_file, 'r') as fp:
        content = yaml.safe_load(fp)
        protocols = content["protocols"]
        car_type = content["car_type"]
        # 判断文件存储路径是否存在,没有则生成目录路径
        work_dir = work_dir + "/pix_"+car_type+"_driver_msgs/msg/"
        if not os.path.exists(work_dir):
            os.makedirs(work_dir)
        # 迭代每一帧生成msg文件
        for protocol in protocols.values():
            msg_file_name = snake_case_to_camel_case(f"{protocol['name']}")
            with open("%s/%s.msg" % (work_dir, msg_file_name), 'w') as pb_fp:
                pb_fp.write("std_msgs/Header header \n")
                write_single_protocol_vars(pb_fp, protocol)
            

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)
    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)

    protocol_conf = os.path.join(conf["output_dir"], conf["protocol_conf"])

    output_dir = conf["output_dir"] 
    gen_proto_file(protocol_conf, output_dir)