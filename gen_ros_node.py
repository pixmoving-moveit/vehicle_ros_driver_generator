#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import datetime
import os
import shutil
import sys
import re

import yaml
from pprint import pprint

from common import common, gen_control_func, gen_report_func

def camel_case_to_snake_case(camel_case: str):
    snake_case = re.sub(r"(?P<key>[A-Z])", r"_\g<key>", camel_case)
    return snake_case.lower().strip('_')

def snake_case_to_camel_case(snake_str):
    return "".join(x.capitalize() for x in snake_str.lower().split("_"))

def gen_control_hpp_node(protocol, send_fmt_val, car_type):
    message_name = protocol["name"]
    camel_message_name = snake_case_to_camel_case(message_name)
    send_fmt_val["car_type"] = car_type
    
    send_fmt_val["include_msgsName_list"] += \
        "".join('#include <pix_%s_driver_msgs/msg/%s.hpp>\n' %
                (car_type, message_name))

    send_fmt_val["include_ParseName_list"] += \
        "".join('#include <pix_%s_driver/%s.hpp>\n' % (car_type, message_name))

    send_fmt_val["subscriber_member_list"] += \
        "".join("rclcpp::Subscription<pix_%s_driver_msgs::msg::%s>::SharedPtr %s_sub_;\n" % (car_type, camel_message_name, message_name))

    send_fmt_val["msg_member_list"] += \
        "".join("pix_%s_driver_msgs::msg::%s::ConstSharedPtr %s_ptr_;\n" %
                (car_type, camel_message_name, message_name))

    send_fmt_val["control_command_structure_list"] += \
        "".join("%s %s_entity_;\n" %
                (camel_message_name, message_name))
        
    send_fmt_val["msg_received_timestamp_list"] += \
        "".join("rclcpp::Time %s_received_time_;\n" % (message_name))

    send_fmt_val["publishing_can_msg_list"] += \
        "".join("can_msgs::msg::Frame::ConstSharedPtr %s_can_ptr_;\n" % (message_name))

    send_fmt_val["callback_function_prototype_list"] += \
        "".join("void callback%s(const pix_%s_driver_msgs::msg::%s::ConstSharedPtr & msg);\n\n" %
        (camel_message_name, car_type, camel_message_name))
    

def gen_control_cpp_node(protocol, send_fmt_val, car_type):
    message_name = protocol["name"]
    camel_message_name = snake_case_to_camel_case(message_name)
    send_fmt_val["car_type"] = car_type
    send_fmt_val["msg_reveived_timestamp_instance_list"] += \
        "".join("%s_received_time_ = this->now();" % (message_name))

    send_fmt_val["subscribe_instance_list"] += \
        "".join('%s_sub_ = create_subscription<pix_%s_driver_msgs::msg::%s>("/pix_%s/%s", 1, std::bind(&ControlCommand::callback%s, this, _1));\n' 
                % (message_name, car_type, camel_message_name, car_type, message_name, camel_message_name))
    
    send_fmt_val["callback_functions_list"] += gen_control_func.gen_callback_func_list(protocol, car_type)

    send_fmt_val["publishing_msg_code_list"] += gen_control_func.gen_publishing_msg_code(protocol, car_type)
    

def gen_report_hpp_node(protocol, recv_fmt_val, car_type):

    message_name = protocol["name"]
    camel_message_name = snake_case_to_camel_case(message_name)
    recv_fmt_val["car_type"] = car_type

    recv_fmt_val["include_msg_list"] += '#include <pix_{car_type}_driver_msgs/msg/{name}.hpp>\n'.format(
        car_type=car_type, name=message_name)

    recv_fmt_val["include_hpp_list"] += '#include <pix_{car_type}_driver/{name}.hpp>\n'.format(
        car_type=car_type, name=message_name)
    
    recv_fmt_val["publisher_list"] += "rclcpp::Publisher<pix_{car_type}_driver_msgs::msg::{camel_name}>::SharedPtr {name}_pub_;\n".format(
        car_type=car_type, camel_name=camel_message_name, name=message_name)

    recv_fmt_val["publish_msg_list"] += "pix_{car_type}_driver_msgs::msg::{camel_name}::ConstSharedPtr {name}_ptr_;\n".format(
        car_type=car_type, camel_name=camel_message_name, name=message_name)

    recv_fmt_val["can_frame_entity_list"] += "{camel_name} {name}_entity_;\n"\
        .format(camel_name=camel_message_name, name=message_name)

    recv_fmt_val["msg_received_time_list"] += "rclcpp::Time {name}_received_time_;\n".format(
        name=message_name
    )

def gen_report_cpp_node(protocol, recv_fmt_val, car_type):
    message_name = protocol["name"]
    camel_message_name = snake_case_to_camel_case(message_name)
    recv_fmt_val["car_type"] = car_type
    
    recv_fmt_val["msg_reveived_timestamp_instance_list"] += "%s_received_time_ = this->now();\n" % (message_name)
    
    recv_fmt_val["publisher_instance_list"] += '%s_pub_ = create_publisher<pix_%s_driver_msgs::msg::%s>("/pix_%s/%s", rclcpp::QoS{1});\n' \
        % (message_name, car_type, camel_message_name, car_type, message_name)
    
    recv_fmt_val["report_msg_list"] += "pix_%s_driver_msgs::msg::%s %s_msg;\n" % (car_type, camel_message_name, message_name)

    recv_fmt_val["parser_case_code_list"] += gen_report_func.gen_parser_case_code_list(protocol, car_type)
    
    recv_fmt_val["report_msg_code_list"] += gen_report_func.gen_report_msg_code_list(protocol, car_type)

def gen_protocols(protocol_conf_file, protocol_dir, car_type):
    # 解析yaml文件，生成c++ ros驱动代码
    # protocol_conf_file yaml文件路径
    # protocol_dir       生成的代码存放路径

    print("Generating canID node cpp")
    # 判断存放路径是否存在
    if not os.path.exists(protocol_dir):
        os.makedirs(protocol_dir)

    # 读取yaml文件内容 到 yaml对象-content
    with open(protocol_conf_file, 'r') as fp:
        content = yaml.safe_load(fp)

    protocols = content["protocols"]
    car_type = content["car_type"]
    # 模板变量的名词：
    
    send_hpp_tmplatee = ["include_msgsName_list", "include_ParseName_list",
                    "subscriber_member_list", "msg_member_list", "control_command_structure_list",
                    "msg_received_timestamp_list",  "publishing_can_msg_list",
                    "callback_function_prototype_list"]
    send_cpp_tmplate = ["msg_reveived_timestamp_instance_list",
                    "subscribe_instance_list", "callback_functions_list", "publishing_msg_code_list"]
    
    recv_hpp_template = ["include_msg_list", "include_hpp_list", "publisher_list",
                     "publish_msg_list", "can_frame_entity_list", "msg_received_time_list"
                     ]
    recv_cpp_template = ["msg_reveived_timestamp_instance_list", "publisher_instance_list", "report_msg_list",
                     "parser_case_code_list", "report_msg_code_list"]
    

    send_hpp_fmt_val = {}
    send_cpp_fmt_val = {}
    recv_hpp_fmt_val = {}
    recv_cpp_fmt_val = {}
    canId_nameInfo = {}  # 存储canId的名称
    canId_nameInfo["report"] = list()
    canId_nameInfo["control"] = list()
    # 初始化
    for i in send_hpp_tmplatee:
        send_hpp_fmt_val[i] = ""
    for i in send_cpp_tmplate:
        send_cpp_fmt_val[i] = ""
    for i in recv_hpp_template:
        recv_hpp_fmt_val[i] = ""
    for i in recv_cpp_template:
        recv_cpp_fmt_val[i] = ""

    for p_name in protocols:
        # print(p_name)
        protocol = protocols[p_name]

        # 根据下发或者上传- 生成相应代码
        if protocol["protocol_type"] == "report":
            canId_nameInfo["report"].append(
                [protocol["name"], [i for i in protocol["vars"]]])
            gen_report_hpp_node(protocol, recv_hpp_fmt_val, car_type)
            gen_report_cpp_node(protocol, recv_cpp_fmt_val, car_type)

        elif protocol["protocol_type"] == "control":
            canId_nameInfo["control"].append(
                [protocol["name"], [i for i in protocol["vars"]]])
            gen_control_hpp_node(protocol, send_hpp_fmt_val, car_type)
            gen_control_cpp_node(protocol, send_cpp_fmt_val, car_type)
        else:
            print("Unknown protocol_type:%s" % protocol["protocol_type"])

    # 读取模板内容并反馈
    control_hpp_tpl_file = "template/control_command.hpp.tpl"
    control_cpp_tpl_file = "template/control_command.cpp.tpl"
    control_node_cpp_tpl_filr = "template/control_command_node.cpp.tpl"
    
    control_hpp_file = protocol_dir + "/pix_" + \
        car_type+"_driver/include/pix_"+car_type+"_driver/control_command.hpp"
    control_cpp_file = protocol_dir + "/pix_" + \
        car_type+"_driver/src/control_command.cpp"
    control_node_cpp_file = protocol_dir + "/pix_" + \
        car_type+"_driver/src/control_command_node.cpp"
    control_hpp_fmt = common.get_tpl_fmt(control_hpp_tpl_file)
    control_cpp_fmt = common.get_tpl_fmt(control_cpp_tpl_file)
    control_node_cpp_fmt = common.get_tpl_fmt(control_node_cpp_tpl_filr)
    print(len(send_hpp_fmt_val))
    with open(control_hpp_file, 'w') as fp:
        fp.write(control_hpp_fmt % send_hpp_fmt_val)
    with open(control_cpp_file, 'w') as fp:
        fp.write(control_cpp_fmt % send_cpp_fmt_val)
    with open(control_node_cpp_file, 'w') as fp:
        fp.write(control_node_cpp_fmt % send_hpp_fmt_val)
    
    report_hpp_tpl_file = "template/report_parser.hpp.tpl"
    report_cpp_tpl_file = "template/report_parser.cpp.tpl"
    report_node_cpp_tpl_file = "template/report_parser_node.cpp.tpl"
    report_hpp_file = protocol_dir + "/pix_" + \
        car_type+"_driver/include/pix_"+car_type+"_driver/report_parser.hpp"
    report_cpp_file = protocol_dir + "/pix_"+car_type+"_driver/src/report_parser.cpp"
    report_node_cpp_file = protocol_dir + "/pix_"+car_type+"_driver/src/report_parser_node.cpp"
    report_hpp_fmt = common.get_tpl_fmt(report_hpp_tpl_file)
    report_cpp_fmt = common.get_tpl_fmt(report_cpp_tpl_file)
    report_node_cpp_fmt = common.get_tpl_fmt(report_node_cpp_tpl_file)
    
    with open(report_hpp_file, 'w') as fp:
        fp.write(report_hpp_fmt % recv_hpp_fmt_val)
    with open(report_cpp_file, 'w') as fp:
        fp.write(report_cpp_fmt % recv_cpp_fmt_val)
    with open(report_node_cpp_file, 'w') as fp:
        fp.write(report_node_cpp_fmt % recv_cpp_fmt_val)
    

    byte_mani_cpp_tpl = "template/Byte.cc.tpl"
    byte_mani_hpp_tpl = "template/Byte.hpp.tpl"
    byte_mani_cpp_FMT = common.get_tpl_fmt(byte_mani_cpp_tpl)
    byte_mani_hpp_FMT = common.get_tpl_fmt(byte_mani_hpp_tpl)
    byte_mani_cpp = protocol_dir + "/pix_"+car_type+"_driver/src/Byte.cc"
    byte_mani_hpp = protocol_dir + "/pix_"+car_type+"_driver/include/pix_"+car_type+"_driver/Byte.hpp"
    with open(byte_mani_cpp, "w") as fp:
        fp.write(byte_mani_cpp_FMT % recv_cpp_fmt_val)
    with open(byte_mani_hpp, "w") as fp:
        fp.write(byte_mani_hpp_FMT)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)

    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)

    protocol_conf = conf["protocol_conf"]
    # protocol_dir = conf["output_cpp_dir"]
    output_dir = conf["output_dir"]

    # 递归删除文件夹所有内容
    shutil.rmtree(output_dir, True)
    os.makedirs(output_dir)
    # generate protocols
    gen_protocols(protocol_conf, "output/src/")
