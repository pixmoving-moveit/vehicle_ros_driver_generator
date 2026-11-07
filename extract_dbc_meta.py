#!/usr/bin/env python3

###############################################################################
# Copyright 2017 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

import re
import shlex
import sys
import os
import yaml


MAX_CAN_ID = 4096000000  # 2048

def camel_case_to_snake_case(camel_case: str):
    snake_case = re.sub(r"([A-Z]+)([A-Z][a-z])", r"\1_\2", camel_case)
    snake_case = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", snake_case)
    return re.sub(r"_+", "_", snake_case).lower().strip('_')

def extract_var_info(items):
    """
       Desp: extract var info from line split items.
    """
    car_var = {}
    car_var["name"] = camel_case_to_snake_case(items[1])
    car_var["bit"] = int(items[3].split('|')[0])
    car_var["len"] = int(items[3].split('|')[1].split('@')[0])
    order_sign = items[3].split('|')[1].split('@')[1]
    if order_sign == "0+":
        car_var["order"] = "motorola"
        car_var["is_signed_var"] = False
    elif order_sign == "0-":
        car_var["order"] = "motorola"
        car_var["is_signed_var"] = True
    elif order_sign == "1+":
        car_var["order"] = "intel"
        car_var["is_signed_var"] = False
    elif order_sign == "1-":
        car_var["order"] = "intel"
        car_var["is_signed_var"] = True
    car_var["offset"] = float(items[4].split(',')[1].split(')')[0])
    car_var["precision"] = float(items[4].split(',')[0].split('(')[1])
    car_var["physical_range"] = items[5]
    car_var["physical_unit"] = items[6]
    if car_var["len"] == 1:
        car_var["type"] = "bool"
    elif car_var["physical_range"].find(
            ".") != -1 or car_var["precision"] != 1.0:
        car_var["type"] = "double"
    else:
        car_var["type"] = "int"
    # print (car_var["name"])
    return car_var

def extract_dbc_meta(dbc_file, out_file, car_type, black_list, sender_list,
                     sender,version_major,version_minor):
    """
        the main gen_config func, use dbc file to gen a yaml file
        parse every line, if the line is:
        eg:BO_ 1104 BMS_0x450: 8 VCU
        5 segments, and segments[0] is "BO_", then begin parse every signal in the following line

    """
    sender_list = set(map(str, sender_list))
    sender_names = {camel_case_to_snake_case(name) for name in sender_list}
    message_locations, signal_locations = {}, {}
    with open(dbc_file, encoding="utf-8") as fp:
        in_protocol = False
        protocols = {}
        protocol = {}
        p_name = ""
        line_num = 0
        for line in fp:
            items = shlex.split(re.sub(r"^(\s*SG_\s+\w+):", r"\1 : ", line))
            line_num = line_num + 1
            if len(items) == 5 and items[0] == "BO_":
                if in_protocol and 0 < len(protocol.get("vars", [])) < 65:
                    protocols[protocol["id"]] = protocol
                in_protocol = False
                p_name = camel_case_to_snake_case(items[2][:-1])
                protocol = {}
                if int(items[1]) > MAX_CAN_ID:
                    continue
                protocol["id"] = "%x" % int(items[1])
                protocol["name"] = "%s" % (p_name)
                protocol["sender"] = items[4]
                if protocol["id"] in black_list:
                    continue
                if p_name in message_locations:
                    previous_name, previous_line = message_locations[p_name]
                    raise ValueError(f"{dbc_file}:{line_num}: messages {previous_name!r} (line {previous_line}) and {items[2][:-1]!r} both normalize to {p_name!r}")
                message_locations[p_name] = (items[2][:-1], line_num)
                signal_locations[protocol["id"]] = []
                protocol["protocol_type"] = "report"
                if (protocol["id"] in sender_list or protocol["sender"] == sender
                        or p_name in sender_names):
                    protocol["protocol_type"] = "control"
                protocol["vars"] = []
                in_protocol = True
            elif in_protocol:
                if len(items) > 3 and items[0] == "SG_":
                    if items[2] == ":":
                        var_info = extract_var_info(items)
                        # current we can't process than 4 byte value
                        if var_info["len"] <= 32:
                            protocol["vars"].append(var_info)
                            signal_locations[protocol["id"]].append((items[1], line_num))
                else:
                    in_protocol = False
                    if len(protocol) != 0 and len(protocol["vars"]) != 0 and len(
                            protocol["vars"]) < 65:
                        protocols[protocol["id"]] = protocol
                        # print protocol
                        protocol = {}

            if len(items) == 5 and items[0] == "CM_" and items[1] == "SG_":
                protocol_id = "%x" % int(items[2])
                if int(items[2]) > MAX_CAN_ID or protocol_id in black_list:
                    continue
                for var in protocols[protocol_id]["vars"]:
                    if var["name"] == camel_case_to_snake_case(items[3]):
                        var["description"] = items[4][:-1]

            if len(items) > 2 and items[0] == "VAL_":
                protocol_id = "%x" % int(items[1])
                if int(items[1]) > MAX_CAN_ID or protocol_id in black_list:
                    continue
                for var in protocols[protocol_id]["vars"]:
                    if var["name"] == camel_case_to_snake_case(items[2]):
                        var["type"] = "enum"
                        var["enum"] = {}
                        for idx in range(3, len(items) - 1, 2):
                            enumtype = re.sub('\W+', ' ', items[idx + 1])
                            enumtype = enumtype.strip().replace(" ",
                                                                "_").upper()
                            enumtype = var["name"].upper() + "_" + enumtype
                            var["enum"][int(items[idx])] = enumtype

        if in_protocol and 0 < len(protocol.get("vars", [])) < 65:
            protocols[protocol["id"]] = protocol

        cpp_reserved_key_words = ['minor', 'major', 'long', 'int', 'auto']
        for key in protocols:
            names = {}
            for var, (raw_name, raw_line) in zip(protocols[key]["vars"], signal_locations[key]):
                if var["name"].lower() in cpp_reserved_key_words:
                    var["name"] = "my_" + var["name"]
                    if "enum" in var:
                        var["enum"] = {value: "MY_" + label for value, label in var["enum"].items()}
                if var["name"] in names:
                    previous_name, previous_line = names[var["name"]]
                    message_name = message_locations[protocols[key]["name"]][0]
                    raise ValueError(f"{dbc_file}:{raw_line}: message {message_name!r} ({key}), signals {previous_name!r} (line {previous_line}) and {raw_name!r} both normalize to {var['name']!r}")
                names[var["name"]] = (raw_name, raw_line)

        # print protocols
        config = {}
        config["car_type"] = car_type
        config["version_major"] = version_major
        config["version_minor"] = version_minor
        config["protocols"] = protocols
        content = yaml.safe_dump(config, allow_unicode=True)
        with open(out_file, 'w', encoding="utf-8") as fp_write:
            fp_write.write(content)
            # print(config)

        control_protocol_num =\
            len([key for key in protocols.keys()
                 if protocols[key]["protocol_type"] == "control"])
        report_protocol_num =\
            len([key for key in protocols.keys()
                 if protocols[key]["protocol_type"] == "report"])
        print("Extract car_type:%s's protocol meta info to file: %s" % (
            car_type.upper(), out_file))
        print("Total parsed protocols: %d" % len(protocols))
        print("Total parsed signals: %d" % sum(len(p["vars"]) for p in protocols.values()))
        print("Control protocols: %d" % control_protocol_num)
        print("Report protocols: %d" % report_protocol_num)
        return True


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\npython %s your_car_parse_config_file.yml" % sys.argv[0])
        sys.exit(0)
    with open(sys.argv[1], 'r', encoding="GB2312") as fp:
        conf = yaml.safe_load(fp)
    dbc_file = os.path.join(conf["config_dir"], conf["dbc_file"])
    protocol_conf = os.path.join(conf["config_dir"], conf["protocol_conf"])
    
    car_type = conf["car_type"]
    black_list = conf["black_list"]
    version_major = conf["version_major"]
    version_minor = conf["version_minor"]
    sender_list = conf["sender_list"]
    sender = conf["sender"]
    extract_dbc_meta(dbc_file, protocol_conf, car_type, black_list,
                     sender_list, sender, version_major, version_minor)
