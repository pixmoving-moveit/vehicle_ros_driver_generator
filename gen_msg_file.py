#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import  yaml
import sys
import os
import re

def snake_case_to_camel_case(snake_str):
    return "".join(x.capitalize() for x in snake_str.lower().split("_"))

def write_single_protocol_constants(pb_fp, p):
    enum_list={}
    for var in p["vars"]:
        if(var["type"]!="enum"):
            continue
        enum_list[var["name"]]=[]
        for key, value in var["enum"].items():
             enum_list[var["name"]].append((key, value))
             enum_list[var["name"]].append((key, value))
    
    enum_list1 = []
    enum_list2 = []
    for key, value in enum_list.items():
        if value in enum_list2:
            index_ = enum_list2.index(value)
            enum_list1[index_][0].append(key)
            
        else:
            enum_list1.append([[key], value])
            enum_list2.append(value)
    i1 = 1  
    for var in enum_list1:
        fmt = "# constants for "

        for name in var[0]:
            fmt = fmt + name + " "
        fmt = fmt + "\n"
        pb_fp.write(fmt)

        fmt = f"uint8 %s_{i1}=%s \n"
        
        for i  in set(var[1]):
            pb_fp.write(fmt%(i[1], i[0]))
        pb_fp.write("\n")
        i1 = i1+1

def write_single_protocol_vars(pb_fp, p):
    """
    解析yaml文件,往msg文件填入信息
    params:
        pb_fp:需要填写内容的文件对象
        p:    yaml对象,帧ID的详细信息
    """
    for var in p["vars"]:
        # 填入msg 定义
        t = var["type"]
        if t == "int":
            t = "int32"
        elif t== "enum":
            t = "int8"
        elif t== "double":
            t = "float32"
        fmt = "%s %s \t"
        pb_fp.write(fmt%(t, var["name"]))

        if "description" in var:
            notes = "# %s [%s] %s\n"%(var["description"], var["physical_unit"], var["physical_range"])
            pb_fp.write(notes)
        else:
            notes = "# %s [%s] %s\n"%("", var["physical_unit"], var["physical_range"])
            pb_fp.write(notes)
        

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
        for pid in protocols:
            p = protocols[pid]
            with open("%s/%s.msg" % (work_dir, snake_case_to_camel_case(p["name"])), 'w') as pb_fp:
                write_single_protocol_constants(pb_fp, p)
                pb_fp.write("\n")
                pb_fp.write("# variables \n")
                pb_fp.write("std_msgs/Header header \n")
                write_single_protocol_vars(pb_fp, p)
            

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)
    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)

    protocol_conf = conf["protocol_conf"]

    output_dir = conf["output_dir"] 
    gen_proto_file(protocol_conf, output_dir)