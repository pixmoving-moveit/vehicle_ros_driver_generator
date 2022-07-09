#include <math.h>
#include <iostream>
#include "ros/ros.h"
#include "can_msgs/Frame.h"
#include "std_msgs/Header.h"

// name = 
// # include "pix pix_driver_msgs/{name}.h"
%(include_pixMsgs_list)s

// # include "{name}.hpp"
%(include_hpp_list)s

static can_msgs::Frame can_frame_msg;

// static ros::Publisher pub_{can_name};
%(global_variable_Publisher_list)s

// static pix_driver_msgs::{name} {name}_msg;
%(global_variable_pixmsg)s

// static {name}.replace('_', '').capitalize()  {name}_entity
%(global_variable_recvEntity)s


// callback func
static void can_callback(const can_msgs::Frame &msg)
{
    can_frame_msg = msg;
    std_msgs::Header header;
    header.frame_id = "pix";
    header.stamp = can_frame_msg.header.stamp;
    %(if_recv_canId)s
}


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "pix_driver_report_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/received_messages", 1, can_callback);

    // pub_{can_name} = nh.advertise<pix_driver_msgs::{name}>("/pix/{can_name}_report", 1, true);
    %(Publisher_include)s
    // add another publisher

    ros::spin();
    return 0;

}
