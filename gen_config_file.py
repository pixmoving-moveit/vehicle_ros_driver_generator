#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import datetime
import os
import shutil
import sys

import yaml
from pprint import pprint
from common import common
# 生成 CMakeList.txt package.xml
def gen_protocols(protocol_conf_file, protocol_dir):
    # 解析yaml文件，生成c++ ros驱动代码
    # protocol_conf_file yaml文件路径 
    # protocol_dir       生成的代码存放路径  
    
    print("Generating canID Config file")
    # 判断存放路径是否存在
    if not os.path.exists(protocol_dir):
        os.makedirs(protocol_dir)
        
    # 读取yaml文件内容 到 yaml对象-content
    with open(protocol_conf_file, 'r') as fp:
        content = yaml.safe_load(fp)  
    protocols = content["protocols"]
    
    

    
    CMakeList = "CMakeLists.txt"
    package = "package.xml"
    
    code_CMake_tpl_file = "template/code_CMakeLists.txt.tpl"
    code_xml_tpl_file = "template/code_package.xml.tpl"
    code_cmake_file = protocol_dir + "pix_driver/" + CMakeList
    code_xml_file = protocol_dir + "pix_driver/" + package
    
    
    msgs_CMake_tpl_file = "template/msgs_CMakeLists.txt.tpl"
    msgs_xml_tpl_file = "template/msgs_package.xml.tpl"
    msgs_cmake_file = protocol_dir + "pix_driver_msgs/" + CMakeList
    msgs_xml_file = protocol_dir + "pix_driver_msgs/" + package
    
    if not os.path.exists(protocol_dir + "/pix_driver_msgs/"):
        os.makedirs(protocol_dir + "/pix_driver_msgs/")
    if not os.path.exists(protocol_dir + "/pix_driver/"):
        os.makedirs(protocol_dir + "/pix_driver/")




    code_CMake_FMT = common.get_tpl_fmt(code_CMake_tpl_file)
    code_xml_FMT = common.get_tpl_fmt(code_xml_tpl_file)
    msgs_CMake_FMT = common.get_tpl_fmt(msgs_CMake_tpl_file)
    msgs_xml_FMT = common.get_tpl_fmt(msgs_xml_tpl_file)
    
    message_name_list = common.get_Name_info(protocols)
    # pprint(message_name_list["control"])
    
    fmt_code_message = {}
    a = ["src/%s.cc\n"% i for i in message_name_list["report"]]
    fmt_code_message["report_cpp_list"] = "".join(a)
    a =  ["src/%s.cc\n"% i for i in message_name_list["control"]]     
    fmt_code_message["command_cpp_list"] = "".join(a)

    with open(code_cmake_file, 'w') as fp:
        fp.write(code_CMake_FMT % fmt_code_message) 
    with open(code_xml_file, 'w') as fp:
        fp.write(code_xml_FMT) 
   
    fmt_msgs_message = {}
    a = message_name_list["report"]
    a.extend(message_name_list["control"])
    # pprint(a)
    a = ["\t%s.msg\n"% i for i in a] 
    fmt_msgs_message["canID_msg_list"] = "".join(a)
    
    with open(msgs_cmake_file, 'w') as fp:
        fp.write(msgs_CMake_FMT % fmt_msgs_message)      
    with open(msgs_xml_file, 'w') as fp:
        fp.write(msgs_xml_FMT) 
    
    
    
    
    
    
    


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)
        
    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)
        
    protocol_conf = config["config_dir"] + conf["protocol_conf"]
    protocol_dir = conf["output_dir"] 
    output_dir = conf["output_dir"]
     
    # 递归删除文件夹所有内容
    shutil.rmtree(output_dir, True)
    os.makedirs(output_dir)
    # generate protocols
    gen_protocols(protocol_conf, protocol_dir)
    # os.makedirs(output_dir+"/dsads/")
    