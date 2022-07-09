#!/usr/bin/env python3
# -*- coding:utf-8 -*-

import datetime
import os
import shutil
import sys

import yaml

from gen_protocols import gen_protocols
from extract_dbc_meta import extract_dbc_meta
import  gen_ros_node
import gen_msg_file
import gen_config_file



def gen(conf):
    """
        doc string:
    """
    dbc_file = conf["config_dir"]  + conf["dbc_file"] 
    protocol_conf_file = conf["config_dir"] + conf["protocol_conf"] 
    car_type = conf["car_type"]
    black_list = conf["black_list"]
    sender_list = conf["sender_list"]
    sender = conf["sender"]
    output_dir = conf["output_dir"]

    # extract dbc file meta to an internal config file
    # 1. dbc 转 yml
    if not extract_dbc_meta(dbc_file, protocol_conf_file, car_type, black_list,
                            sender_list, sender):
        return

    # gen proto
    # proto_dir = output_dir + "proto/"
    # gen_proto_file(protocol_conf_file, proto_dir)

    # gen protocol  
    # 2. 代码生成 - 解析can原始
    # protocol_dir = output_dir + "vehicle/" 
    gen_protocols(protocol_conf_file, output_dir)

    # 3. 代码生成 - 生成订阅发布ros节点
    gen_ros_node.gen_protocols(protocol_conf_file, output_dir)
    # msg文件生成
    gen_msg_file.gen_proto_file(protocol_conf_file, output_dir)
    # 编译文件生成
    gen_config_file.gen_protocols(protocol_conf_file, output_dir)
    
    
    


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)
    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)
    gen(conf)
