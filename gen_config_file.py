#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import datetime
import os
import shutil
import sys

import yaml
from pprint import pprint
from common import common


# ���� CMakeList.txt package.xml
def gen_protocols(protocol_conf_file, protocol_dir):
    # ����yaml�ļ�������c++ ros��������
    # protocol_conf_file yaml�ļ�·��
    # protocol_dir       ���ɵĴ�����·��

    print("Generating canID Config file")
    # �жϴ��·���Ƿ����
    if not os.path.exists(protocol_dir):
        os.makedirs(protocol_dir)

    # ��ȡyaml�ļ����� �� yaml����-content
    with open(protocol_conf_file, 'r') as fp:
        content = yaml.safe_load(fp)
    protocols = content["protocols"]

    car_type = content["car_type"]

    CMakeList = "CMakeLists.txt"
    package = "package.xml"

    code_CMake_tpl_file = "template/code_CMakeLists.txt.tpl"
    code_xml_tpl_file = "template/code_package.xml.tpl"
    code_cmake_file = protocol_dir + "/pix_"+car_type+"_driver/" + CMakeList
    code_xml_file = protocol_dir + "/pix_"+car_type+"_driver/" + package

    msgs_CMake_tpl_file = "template/msgs_CMakeLists.txt.tpl"
    msgs_xml_tpl_file = "template/msgs_package.xml.tpl"
    msgs_cmake_file = protocol_dir + "/pix_"+car_type+"_driver_msgs/" + CMakeList
    msgs_xml_file = protocol_dir + "/pix_"+car_type+"_driver_msgs/" + package

    if not os.path.exists(protocol_dir + "/pix_"+car_type+"_driver_msgs/"):
        os.makedirs(protocol_dir + "/pix_"+car_type+"_driver_msgs/")
    if not os.path.exists(protocol_dir + "/pix_"+car_type+"_driver/"):
        os.makedirs(protocol_dir + "/pix_"+car_type+"_driver/")

    code_CMake_FMT = common.get_tpl_fmt(code_CMake_tpl_file)
    code_xml_FMT = common.get_tpl_fmt(code_xml_tpl_file)
    msgs_CMake_FMT = common.get_tpl_fmt(msgs_CMake_tpl_file)
    msgs_xml_FMT = common.get_tpl_fmt(msgs_xml_tpl_file)

    message_name_list = common.get_Name_info(protocols)
    # pprint(message_name_list["control"])

    fmt_code_message = {}
    a = ["src/%s.cc\n" % i for i in message_name_list["report"]]
    fmt_code_message["report_cpp_list"] = "".join(a)
    a = ["src/%s.cc\n" % i for i in message_name_list["control"]]
    fmt_code_message["command_cpp_list"] = "".join(a)
    fmt_code_message["car_type"] = car_type

    fmt_code_xml_message = {}
    fmt_code_xml_message["car_type"] = car_type

    with open(code_cmake_file, 'w') as fp:
        fp.write(code_CMake_FMT % fmt_code_message)
    with open(code_xml_file, 'w') as fp:
        fp.write(code_xml_FMT % fmt_code_xml_message)

    fmt_msgs_message = {}
    a = message_name_list["report"]
    a.extend(message_name_list["control"])
    # pprint(a)
    a = ["\t%s.msg\n" % i for i in a]
    fmt_msgs_message["canID_msg_list"] = "".join(a)
    fmt_msgs_message["car_type"] = car_type

    fmt_msg_xml_message = {}
    fmt_msg_xml_message["car_type"] = car_type

    with open(msgs_cmake_file, 'w') as fp:
        fp.write(msgs_CMake_FMT % fmt_msgs_message)
    with open(msgs_xml_file, 'w') as fp:
        fp.write(msgs_xml_FMT % fmt_msg_xml_message)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)

    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)

    protocol_conf = config["config_dir"] + conf["protocol_conf"]
    protocol_dir = conf["output_dir"]
    output_dir = conf["output_dir"]

    # �ݹ�ɾ���ļ�����������
    shutil.rmtree(output_dir, True)
    os.makedirs(output_dir)
    # generate protocols
    gen_protocols(protocol_conf, protocol_dir)
    # os.makedirs(output_dir+"/dsads/")
