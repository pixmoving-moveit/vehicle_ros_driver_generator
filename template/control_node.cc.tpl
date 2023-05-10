#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>

#include <can_msgs/msg/frame.hpp>


// include- msgs header file
// Example: #include "pix_driver_msgs/BrakeCommand.h"
// #include pix_driver_msgs/protocols["name"].h
%(include_msgsName_list)s


// include- Parse header file
// Example: #include "brake_command_101.hpp"
// #include protocols["name"].cpp
%(include_ParseName_list)s

namespace pix_%[car_type]s_driver
{
namespace control_command
{

/**
 * @brief param structure of control command node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 * @param command_timeout_ms timeout threshold of control command msg from control converter in ms
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
  int command_timeout_ms;
};

%(global_variable_vehicle_msg)s
%(global_variable_ros_msg)s

// global variable:  send entity
// Example: static Brakecommand101 brake_command;
// static protocols["name"] protocols["name"]_entity;
%(global_variable_sendEntity)s


// global variable: Enable and send time stamp
/*
Example:
static bool brake_enable, gear_enable, park_enable, steer_enable, throttle_enable;
static int brake_prev_t=0, gear_prev_t=0, park_prev_t=0, steer_prev_t=0, throttle_prev_t=0;

protocols["name"].split("_",1)[0]_enable, ...
protocols["name"].split("_",1)[0]_prev_t=0, ...
*/
static bool %(global_variable_Enable)s
static int %(global_variable_sendTimeStamp)s


static int time_diff = 100000000;
static ros::Publisher pub_can;


// define send canID callback function
%(sendCanID_callback_func_list)s


//  define timer callback function
void timer_callback(const ros::TimerEvent &te)
{
    int now;
    now = ros::Time::now().toNSec();
    /*Example: 
    // brake
    if(now-brake_prev_t>time_diff)
    {
        for(uint i=0;i<8;i++)
        {   
            can_brake.id = brake_command.ID;
            can_brake.data[i] = 0;
        }
        pub_can.publish(can_brake);
    }
    else{
        pub_can.publish(can_brake);   
    }
    */
    %(if_canID_prev_t)s
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "pix_%(car_type)s_driver_command_node");
    ros::NodeHandle nh;

    // creat ros Subscriber
    // Example: ros::Subscriber sub_brake = nh.subscribe("/pix/brake_command", 1, brake_callback);
    %(gen_Subscriber_list)s
    //  creat ros publisher
    pub_can = nh.advertise<can_msgs::Frame>("/sent_messages", 10, false);

    ros::Timer set_speed = nh.createTimer(ros::Duration(1/50.0), timer_callback);
    ros::spin();

    return 0;

}

} // control_command
} // pix_%{car_type}s_driver