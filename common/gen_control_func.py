#!/usr/bin/env python3
# -*- coding: utf-8 -*-
def msg_signal_list(protocol):
    # 获取canID的msg信号
    # protocol  canID的信号信息 yam对象
    prefix = "\t%s_msg."%(protocol["name"])
    signal_list = []
    for var in protocol["vars"]:
        signal_list.append(var["name"]+",\n")
        
    result = "%s_msg."%(protocol["name"]) + prefix.join(signal_list)[:-2]
    
    return result

# msg 到 can原始函数
def sendCanID_callback_func_list(protocol):
    message_name = protocol["name"]
    func = """\nstatic void %s_callback(const pix_driver_msgs::%s &msg)
{
    """%(message_name.split("_",1)[0], message_name)

    fmt = """
    {name}_entity.Reset();
    {name}_msg = msg;
    can_{can_name}.header.stamp = ros::Time::now();
    can_{can_name}.dlc = 8;
    {name}_entity.UpdateData(
        {name_msg_signal_list}
    );
    can_{can_name}.id = {name}_entity.ID;
    can_{can_name}.is_extended= false;
    uint8_t *A;
    A = {name}_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {{
        can_{can_name}.data[i] = *A;
        A += 1;
    }}
    int t_nsec = 0;
    t_nsec = can_{can_name}.header.stamp.toNSec();
    {can_name}_prev_t = t_nsec;
}}\n
    """.format(name=message_name, \
        can_name=message_name.split("_",1)[0], \
        name_msg_signal_list=msg_signal_list(protocol))
    return func + fmt

# timer_callback_func 时间回调函数
def timer_callback_func(protocol):
    message_name = protocol["name"]
    if_canID_prev_t = """
    // {can_name}
    if(now - {can_name}_prev_t>30000000)
    {{
        for(uint i=0; i<8; i++)
        {{   
            can_{can_name}.id = {name}_entity.ID;
            can_{can_name}.data[i] = 0;
        }}
        pub_can.publish(can_{can_name});
    }}
    else{{
        pub_can.publish(can_{can_name});
    }}
    """.format(name=message_name, \
        can_name=message_name.split("_",1)[0])
    
    return if_canID_prev_t

def gen_Subscriber_list(protocol):
    message_name = protocol["name"]
    template = 'ros::Subscriber sub_{can_name} = nh.subscribe("/pix/{name}", 1, {can_name}_callback);\n\t'
    return template.format(name=message_name.rsplit("_", 1)[0], can_name=message_name.split("_",1)[0])