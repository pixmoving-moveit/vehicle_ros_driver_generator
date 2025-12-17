#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re

def camel_case_to_snake_case(camel_case: str):
    snake_case = re.sub(r"(?P<key>[A-Z])", r"_\g<key>", camel_case)
    return snake_case.lower().strip('_')

def snake_case_to_camel_case(snake_str: str):
    return "".join(x.capitalize() for x in snake_str.lower().split("_"))

def gen_parser_case_code_list(protocol, car_type):
    message_name = f"{protocol['name']}"
    camel_message_name = snake_case_to_camel_case(message_name)

    assign_variable_list = ""
    for v in protocol['vars']:
        assign_variable_list += "    {name}_msg.{var} = {name}_parser_.{var}_;\n".format(
            name=message_name, var=v["name"]
        )
    
    code = """
  case {camel_message_name}::ID:
    for(uint i=0;i<8;i++)
    {{
      byte_temp[i] = msg->data[i];
    }}
    {message_name}_parser_.update_bytes(byte_temp);
    {message_name}_parser_.Parse();

    {message_name}_msg.header = header;
{assign_variable_list}
    {message_name}_pub_->publish({message_name}_msg);
    break;
    """.format(camel_message_name=camel_message_name, message_name=message_name, assign_variable_list=assign_variable_list, car_type=car_type)
    return code

def can_callback_if(canId_nameInfo):
    # canId_nameInfo =[throttle_command_100, [vars_name]]
    # print(canId_nameInfo)
    canName = canId_nameInfo[0]
    varNameList = canId_nameInfo[1]
    # print(canName)
    fmt="""
    if(can_frame_msg.id=={name}_parse.ID)
    {{
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {{
        byte_temp[i] = can_frame_msg.data[i];
        }}
        {name}_parse.update_bytes(byte_temp);
        {name}_parse.Parse();
        {name}_msg.header = header;
{var_name_list}
        pub_{can_name}.publish({name}_msg);
    }}
    """.format(name=canId_nameInfo[0], can_name=canName.rsplit('_', 1)[0],\
        var_name_list=var_name_assignment(canName, varNameList))
    
    return fmt


def var_name_assignment(canName, varNameList):
    # canId_nameInfo =[throttle_command_100, [vars_name]]
    prefix = "\t\t{name}_msg.{var_raw} = {name}_parse.{var_lower};\n"
    var_name_list = list()
    for i in varNameList:
        var_name_list.append(prefix.format(name=canName, var_raw=i, var_lower=i.lower()))

    return "".join(var_name_list)
