#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re

def camel_case_to_snake_case(camel_case: str):
    snake_case = re.sub(r"(?P<key>[A-Z])", r"_\g<key>", camel_case)
    return snake_case.lower().strip('_')

def snake_case_to_camel_case(snake_str):
    return "".join(x.capitalize() for x in snake_str.lower().split("_"))

def msg_signal_list(protocol):
    # 获取canID的msg信号
    # protocol  canID的信号信息 yam对象
    prefix = "\t%s_msg."%(protocol["name"])
    signal_list = []
    for var in protocol["vars"]:
        signal_list.append(var["name"]+",\n")
        
    result = "%s_msg."%(protocol["name"]) + prefix.join(signal_list)[:-2]
     
    return result

def gen_callback_func_list(protocol, car_type):
    message_name = protocol["name"]
    camel_message_name = snake_case_to_camel_case(message_name)
    var_list = ""
    for v in protocol['vars']:
        var_list += "msg->%s, " % (v['name'])
    func = """\n
    void ControlCommand::callback{camel_message_name}(const pix_{car_type}_driver_msgs::msg::{camel_message_name}::ConstSharedPtr & msg)
    {{
        {message_name}_received_time_ = this->now();
        {message_name}_ptr_ = msg;
        {message_name}_entity_.Reset();
        {message_name}_entity_.UpdateData({var_list});
        can_msgs::msg::Frame {message_name}_can_msg;
        {message_name}_can_msg.header.stamp = msg->header.stamp;
        {message_name}_can_msg.dlc = 8;
        {message_name}_can_msg.id = {message_name}_entity_.ID;
        {message_name}_can_msg.is_extended = false;
        uint8_t *signal_bits;
        signal_bits = {message_name}_entity_.get_data();
        for (int i = 0; i < 8; i++)
        {{
            {message_name}_can_msg.data[i] = *signal_bits;
            signal_bits += 1;
        }}
        {message_name}_can_ptr_ = std::make_shared<can_msgs::msg::Frame>({message_name}_can_msg);
    }}\n
    """.format(camel_message_name=camel_message_name, car_type=car_type, var_list=var_list[:-2], message_name=message_name)
    return func

def gen_publishing_msg_code(protocol, car_type):
    message_name = protocol["name"]
    camel_message_name = snake_case_to_camel_case(message_name)
    func = """\n
    // {message_name}
    const double {message_name}_delta_time_ms =
        (current_time - {message_name}_received_time_).seconds() * 1000.0;
    if ({message_name}_delta_time_ms > param_.command_timeout_ms || {message_name}_can_ptr_==nullptr) {{
        RCLCPP_ERROR_THROTTLE(
        get_logger(), *this->get_clock(), std::chrono::milliseconds(5000).count(),
        "{message_name} timeout = %f ms.", {message_name}_delta_time_ms);
    }} else {{
        can_frame_pub_->publish(*{message_name}_can_ptr_);
    }}\n
    """.format(
       message_name=message_name
    )
    return func

# msg 到 can原始函数
def sendCanID_callback_func_list(protocol, car_type):
    message_name = protocol["name"]
    func = """\nstatic void %s_callback(const pix_%s_driver_msgs::%s &msg)
{
    """%(message_name, car_type, message_name)

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
        can_name=message_name, \
        name_msg_signal_list=msg_signal_list(protocol))
    return func + fmt

# timer_callback_func 时间回调函数
def timer_callback_func(protocol):
    message_name = protocol["name"]
    if_canID_prev_t = """
    // {can_name}
    if(now - {can_name}_prev_t>time_diff)
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
        can_name=message_name)
    
    return if_canID_prev_t

def gen_Subscriber_list(protocol, car_type):
    message_name = protocol["name"]
    template = 'ros::Subscriber sub_{can_name} = nh.subscribe("/pix_{car_type}/{name}", 1, {can_name}_callback);\n\t'
    # return template.format(name=message_name.rsplit("_", 1)[0], can_name=message_name.rsplit("_",1)[0])
    return template.format(car_type=car_type, name=message_name, can_name=message_name)