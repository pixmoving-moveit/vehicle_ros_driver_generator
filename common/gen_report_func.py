#!/usr/bin/env python3
# -*- coding: utf-8 -*-
def can_callback_if(canId_nameInfo):
    # canId_nameInfo =[throttle_command_100, [vars_name]]
    # print(canId_nameInfo)
    canName = canId_nameInfo[0]
    varNameList = canId_nameInfo[1]
    # print(canName)
    fmt="""
    if(can_frame_msg.id=={name}_entity.ID)
    {{
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {{
        byte_temp[i] = can_frame_msg.data[i];
        }}
        {name}_entity.update_bytes(byte_temp);
        {name}_entity.Parse();
        {name}_msg.header = header;
{var_name_list}
        pub_{can_name}.publish({name}_msg);
    }}
    """.format(name=canId_nameInfo[0], can_name=canName.rsplit('_', 1)[0],\
        var_name_list=var_name_assignment(canName, varNameList))
    
    return fmt


def var_name_assignment(canName, varNameList):
    # canId_nameInfo =[throttle_command_100, [vars_name]]
    prefix = "\t\t{name}_msg.{var_raw} = {name}_entity.{var_lower};\n"
    var_name_list = list()
    for i in varNameList:
        var_name_list.append(prefix.format(name=canName, var_raw=i, var_lower=i.lower()))

    return "".join(var_name_list)
