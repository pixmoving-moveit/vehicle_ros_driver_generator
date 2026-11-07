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
    message_name = f'{protocol["name"]}'
    camel_message_name = snake_case_to_camel_case(message_name)
    send_fmt_val["car_type"] = car_type
    
    send_fmt_val["include_msgsName_list"] += \
        "".join('#include <pix_%s_driver_msgs/msg/%s.hpp>\n' %
                (car_type, message_name))

    send_fmt_val["include_ParseName_list"] += \
        "".join('#include <libs/%s.hpp>\n' % (message_name))

    send_fmt_val["delay_recording_definition_list"] += \
        "".join('  DelayRecording %s_delay_;\n' % message_name)

    send_fmt_val["is_pix_interface_definition_list"] += \
        "".join('  bool %s_issub_;\n' % message_name)

    send_fmt_val["subscriber_member_list"] += \
        "".join("  rclcpp::Subscription<pix_{car_type}_driver_msgs::msg::{camel_message_name}>::SharedPtr {message_name}_sub_;\n".format(car_type=car_type, camel_message_name=camel_message_name, message_name=message_name))

    send_fmt_val["msg_member_list"] += \
        "".join("  pix_%s_driver_msgs::msg::%s::ConstSharedPtr %s_ptr_;\n" %
                (car_type, camel_message_name, message_name))

    send_fmt_val["control_command_structure_list"] += \
        "".join("  %s %s_parse_;\n" %
                (camel_message_name, message_name))
        
    send_fmt_val["msg_received_timestamp_list"] += \
        "".join("  rclcpp::Time %s_received_time_;\n" % (message_name))

    send_fmt_val["publishing_can_msg_list"] += \
        "".join("  can_msgs::msg::Frame::ConstSharedPtr %s_can_ptr_;\n" % (message_name))

    send_fmt_val["callback_function_prototype_list"] += \
        "".join("  void callback%s(const pix_%s_driver_msgs::msg::%s::ConstSharedPtr & msg);\n" %
        (camel_message_name, car_type, camel_message_name))
    

def gen_control_cpp_node(protocol, send_fmt_val, car_type):
    message_name = f'{protocol["name"]}'
    camel_message_name = snake_case_to_camel_case(message_name)
    send_fmt_val["car_type"] = car_type

    send_fmt_val["subscribe_instance_list"] += \
        "".join('    {message_name}_sub_ = create_subscription<pix_{car_type}_driver_msgs::msg::{camel_message_name}>("/pix_{car_type}/{message_name}", 10, std::bind(&ControlCommand::callback{camel_message_name}, this, _1));\n' 
            .format(message_name=message_name, car_type=car_type, camel_message_name=camel_message_name))
    
    send_fmt_val["delay_recording_init_list"] += \
        "".join('  %s_delay_.count_eorro = 0;\n  %s_delay_.count_waring = 0;\n' % (message_name, message_name)) 

    send_fmt_val["is_pix_interface_init_list"] += \
        "".join('  %s_issub_ = false;\n' % message_name)

    send_fmt_val["msg_reveived_timestamp_instance_list"] += \
        "".join("  %s_received_time_ = this->now();\n" % (message_name))
    
    send_fmt_val["callback_functions_list"] += gen_control_func.gen_callback_func_list(protocol, car_type)

    send_fmt_val["if_pix_interface_definition_list"] += \
        "".join('  if(!{message_name}_issub_) return;\n'.format(message_name=message_name))
    
    send_fmt_val["if_msg_received_timestamp_list"] += gen_control_func.msg_received_timestamp_code(protocol, car_type)

    send_fmt_val["on_delayed_alarm_list"] += \
        "".join("""
  stat.addf("{message_name} count_eorro", "%%d", {message_name}_delay_.count_eorro); 
  stat.addf("{message_name} count_warn", "%%d", {message_name}_delay_.count_waring);
    """.format(message_name=message_name))

def gen_report_hpp_node(protocol, recv_fmt_val, car_type):

    message_name = f'{protocol["name"]}'
    camel_message_name = snake_case_to_camel_case(message_name)
    recv_fmt_val["car_type"] = car_type

    recv_fmt_val["include_msg_list"] += '#include <pix_{car_type}_driver_msgs/msg/{name}.hpp>\n'.format(
        car_type=car_type, name=message_name)

    recv_fmt_val["include_hpp_list"] += '#include <libs/{name}.hpp>\n'.format(
        car_type=car_type, name=message_name)
    
    recv_fmt_val["publisher_list"] += "  rclcpp::Publisher<pix_{car_type}_driver_msgs::msg::{camel_name}>::SharedPtr {name}_pub_;\n".format(
        car_type=car_type, camel_name=camel_message_name, name=message_name)

    recv_fmt_val["publisher_msg_list"] += "  {camel_name} {name}_parser_;\n".format(camel_name=camel_message_name, name=message_name)
    
def gen_report_cpp_node(protocol, recv_fmt_val, car_type):
    message_name = f'{protocol["name"]}'
    camel_message_name = snake_case_to_camel_case(message_name)
    recv_fmt_val["car_type"] = car_type
    
    recv_fmt_val["publisher_instance_list"] += '    {message_name}_pub_ = create_publisher<pix_{car_type}_driver_msgs::msg::{camel_message_name}>("/pix_{car_type}/{message_name}", rclcpp::QoS{{10}});\n' \
        .format(message_name=message_name, car_type=car_type, camel_message_name=camel_message_name)
    
    recv_fmt_val["report_msg_list"] += "  pix_%s_driver_msgs::msg::%s %s_msg;\n" % (car_type, camel_message_name, message_name)

    recv_fmt_val["parser_case_code_list"] += gen_report_func.gen_parser_case_code_list(protocol, car_type)

def gen_ros2_version(recv_fmt_val, version_major, version_minor):
    recv_fmt_val["version_major"] = version_major
    recv_fmt_val["version_minor"] = version_minor

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
                    "delay_recording_definition_list",
                    "is_pix_interface_definition_list",
                    "callback_function_prototype_list"]
    send_cpp_tmplate = [
        "subscribe_instance_list", 
        "callback_functions_list", 
        "on_delayed_alarm_list",
        "if_pix_interface_definition_list",
        "if_msg_received_timestamp_list",
        "delay_recording_init_list",
        "is_pix_interface_init_list",
        "msg_reveived_timestamp_instance_list"
    ]
    
    recv_hpp_template = ["include_msg_list", "include_hpp_list", "publisher_list",
                        "publisher_msg_list", "can_frame_parse_list"]
    
    recv_cpp_template = ["publisher_instance_list", "report_msg_list",
                     "parser_case_code_list"]
    

    send_hpp_fmt_val = {}
    send_cpp_fmt_val = {}
    ros2_version_fmt_val = {}
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
            gen_ros2_version(ros2_version_fmt_val, content["version_major"], content["version_minor"])
        else:
            print("Unknown protocol_type:%s" % protocol["protocol_type"])

    # 读取模板内容并反馈
    control_hpp_tpl_file = "template/ros2_control_command.hpp.tpl"
    control_cpp_tpl_file = "template/ros2_control_command.cpp.tpl"
    
    control_hpp_file = protocol_dir + "/pix_" + \
        car_type+"_driver/include/pix_"+car_type+"_driver/control_command.hpp"
    if not os.path.exists(os.path.dirname(control_hpp_file)):
        os.makedirs(os.path.dirname(control_hpp_file))  # 创建多级目录
    control_cpp_file = protocol_dir + "/pix_" + \
        car_type+"_driver/src/control_command.cpp"
    control_hpp_fmt = common.get_tpl_fmt(control_hpp_tpl_file)
    control_cpp_fmt = common.get_tpl_fmt(control_cpp_tpl_file)
    with open(control_hpp_file, 'w') as fp:
        fp.write(control_hpp_fmt % send_hpp_fmt_val)
    with open(control_cpp_file, 'w') as fp:
        fp.write(control_cpp_fmt % send_cpp_fmt_val)
    
    report_hpp_tpl_file = "template/ros2_report_parser.hpp.tpl"
    report_cpp_tpl_file = "template/ros2_report_parser.cpp.tpl"
    report_hpp_file = protocol_dir + "/pix_" + \
        car_type+"_driver/include/pix_"+car_type+"_driver/report_parser.hpp"
    report_cpp_file = protocol_dir + "/pix_"+car_type+"_driver/src/report_parser.cpp"
    report_hpp_fmt = common.get_tpl_fmt(report_hpp_tpl_file)
    report_cpp_fmt = common.get_tpl_fmt(report_cpp_tpl_file)
    
    ros2_version_file =  protocol_dir + "/pix_" + \
        car_type+"_driver/include/pix_"+car_type+"_driver/version.hpp"
    ros2_version_tpl_file = "template/ros2_version.hpp.tpl"
    ros2_version_fmt = common.get_tpl_fmt(ros2_version_tpl_file)
    
    with open(report_hpp_file, 'w') as fp:
        fp.write(report_hpp_fmt % recv_hpp_fmt_val)
    with open(report_cpp_file, 'w') as fp:
        fp.write(report_cpp_fmt % recv_cpp_fmt_val)
    with open(ros2_version_file, 'w') as fp:
        fp.write(ros2_version_fmt % ros2_version_fmt_val)
    
    source_folder = "template/launch"
    destination_folder =  protocol_dir + "/pix_" + car_type+"_driver/launch"
    if os.path.exists(destination_folder):
        shutil.rmtree(destination_folder)
    # 拷贝文件夹
    shutil.copytree(source_folder, destination_folder)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)

    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)

    output_dir = conf["output_dir"]
    protocol_conf = os.path.join(conf["protocol_conf"], conf["protocol_conf"])
    car_type = conf["car_type"]

    # generate protocols
    gen_protocols(protocol_conf, output_dir, car_type)
