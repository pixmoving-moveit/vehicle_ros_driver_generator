#include "ros/ros.h"
#include "can_msgs/Frame.h"


// include- msgs header file
// Example: #include "pix_driver_msgs/BrakeCommand.h"
// #include pix_driver_msgs/protocols["name"].h
#include "pix_driver_msgs/throttle_command_100.h"
#include "pix_driver_msgs/brake_command_101.h"
#include "pix_driver_msgs/steering_command_102.h"
#include "pix_driver_msgs/gear_command_103.h"
#include "pix_driver_msgs/park_command_104.h"
#include "pix_driver_msgs/vehicle_mode_command_105.h"
#include "pix_driver_msgs/acu_sweepctrlcmd_107.h"



// include- Parse header file
// Example: #include "brake_command_101.hpp"
// #include protocols["name"].cpp
#include "throttle_command_100.hpp"
#include "brake_command_101.hpp"
#include "steering_command_102.hpp"
#include "gear_command_103.hpp"
#include "park_command_104.hpp"
#include "vehicle_mode_command_105.hpp"
#include "acu_sweepctrlcmd_107.hpp"



// global variable: msg
/*
Example:
static can_msgs::Frame can_brake;
static pix_driver_msgs::BrakeCommand brake_command_msg;

static can_msgs::Frame can_protocols["name"].split("_",1)[0];
static pix_driver_msgs::protocols["name"] protocols["name"]_msg
*/
static pix_driver_msgs::throttle_command_100 throttle_command_100_msg;
static pix_driver_msgs::brake_command_101 brake_command_101_msg;
static pix_driver_msgs::steering_command_102 steering_command_102_msg;
static pix_driver_msgs::gear_command_103 gear_command_103_msg;
static pix_driver_msgs::park_command_104 park_command_104_msg;
static pix_driver_msgs::vehicle_mode_command_105 vehicle_mode_command_105_msg;
static pix_driver_msgs::acu_sweepctrlcmd_107 acu_sweepctrlcmd_107_msg;

static can_msgs::Frame can_throttle;
static can_msgs::Frame can_brake;
static can_msgs::Frame can_steering;
static can_msgs::Frame can_gear;
static can_msgs::Frame can_park;
static can_msgs::Frame can_vehicle;
static can_msgs::Frame can_acu;


// global variable:  send entity
// Example: static Brakecommand101 brake_command;
// static protocols["name"] protocols["name"]_entity;
static Throttlecommand100 throttle_command_100_entity;
static Brakecommand101 brake_command_101_entity;
static Steeringcommand102 steering_command_102_entity;
static Gearcommand103 gear_command_103_entity;
static Parkcommand104 park_command_104_entity;
static Vehiclemodecommand105 vehicle_mode_command_105_entity;
static Acusweepctrlcmd107 acu_sweepctrlcmd_107_entity;



// global variable: Enable and send time stamp
/*
Example:
static bool brake_enable, gear_enable, park_enable, steer_enable, throttle_enable;
static int brake_prev_t=0, gear_prev_t=0, park_prev_t=0, steer_prev_t=0, throttle_prev_t=0;

protocols["name"].split("_",1)[0]_enable, ...
protocols["name"].split("_",1)[0]_prev_t=0, ...
*/
static bool throttle_enable, brake_enable, steering_enable, gear_enable, park_enable, vehicle_enable, acu_enable;
static int throttle_prev_t=0, brake_prev_t=0, steering_prev_t=0, gear_prev_t=0, park_prev_t=0, vehicle_prev_t=0, acu_prev_t=0;


int time_diff = 200000;
static ros::Publisher pub_can;


// define send canID callback function

static void throttle_callback(const pix_driver_msgs::throttle_command_100 &msg)
{
    
    throttle_command_100_entity.Reset();
    throttle_command_100_msg = msg;
    can_throttle.header.stamp = ros::Time::now();
    can_throttle.dlc = 8;
    throttle_command_100_entity.UpdateData(
        throttle_command_100_msg.Dirve_SpeedTarget,
	throttle_command_100_msg.CheckSum_100,
	throttle_command_100_msg.Dirve_ThrottlePedalTarget,
	throttle_command_100_msg.Dirve_EnCtrl
    );
    can_throttle.id = throttle_command_100_entity.ID;
    can_throttle.is_extended= false;
    uint8_t *A;
    A = throttle_command_100_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {
        can_throttle.data[i] = *A;
        A += 1;
    }
    int t_nsec = 0;
    t_nsec = can_throttle.header.stamp.toNSec();
    throttle_prev_t = t_nsec;
}

    
static void brake_callback(const pix_driver_msgs::brake_command_101 &msg)
{
    
    brake_command_101_entity.Reset();
    brake_command_101_msg = msg;
    can_brake.header.stamp = ros::Time::now();
    can_brake.dlc = 8;
    brake_command_101_entity.UpdateData(
        brake_command_101_msg.CheckSum_101,
	brake_command_101_msg.Brake_Pedal_Target,
	brake_command_101_msg.Brake_EnCtrl
    );
    can_brake.id = brake_command_101_entity.ID;
    can_brake.is_extended= false;
    uint8_t *A;
    A = brake_command_101_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {
        can_brake.data[i] = *A;
        A += 1;
    }
    int t_nsec = 0;
    t_nsec = can_brake.header.stamp.toNSec();
    brake_prev_t = t_nsec;
}

    
static void steering_callback(const pix_driver_msgs::steering_command_102 &msg)
{
    
    steering_command_102_entity.Reset();
    steering_command_102_msg = msg;
    can_steering.header.stamp = ros::Time::now();
    can_steering.dlc = 8;
    steering_command_102_entity.UpdateData(
        steering_command_102_msg.Steer_EnCtrl,
	steering_command_102_msg.Steer_AngleTarget,
	steering_command_102_msg.Steer_AngleSpeed,
	steering_command_102_msg.CheckSum_102
    );
    can_steering.id = steering_command_102_entity.ID;
    can_steering.is_extended= false;
    uint8_t *A;
    A = steering_command_102_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {
        can_steering.data[i] = *A;
        A += 1;
    }
    int t_nsec = 0;
    t_nsec = can_steering.header.stamp.toNSec();
    steering_prev_t = t_nsec;
}

    
static void gear_callback(const pix_driver_msgs::gear_command_103 &msg)
{
    
    gear_command_103_entity.Reset();
    gear_command_103_msg = msg;
    can_gear.header.stamp = ros::Time::now();
    can_gear.dlc = 8;
    gear_command_103_entity.UpdateData(
        gear_command_103_msg.Gear_Target,
	gear_command_103_msg.Gear_EnCtrl,
	gear_command_103_msg.CheckSum_103
    );
    can_gear.id = gear_command_103_entity.ID;
    can_gear.is_extended= false;
    uint8_t *A;
    A = gear_command_103_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {
        can_gear.data[i] = *A;
        A += 1;
    }
    int t_nsec = 0;
    t_nsec = can_gear.header.stamp.toNSec();
    gear_prev_t = t_nsec;
}

    
static void park_callback(const pix_driver_msgs::park_command_104 &msg)
{
    
    park_command_104_entity.Reset();
    park_command_104_msg = msg;
    can_park.header.stamp = ros::Time::now();
    can_park.dlc = 8;
    park_command_104_entity.UpdateData(
        park_command_104_msg.CheckSum_104,
	park_command_104_msg.Park_Target,
	park_command_104_msg.Park_EnCtrl
    );
    can_park.id = park_command_104_entity.ID;
    can_park.is_extended= false;
    uint8_t *A;
    A = park_command_104_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {
        can_park.data[i] = *A;
        A += 1;
    }
    int t_nsec = 0;
    t_nsec = can_park.header.stamp.toNSec();
    park_prev_t = t_nsec;
}

    
static void vehicle_callback(const pix_driver_msgs::vehicle_mode_command_105 &msg)
{
    
    vehicle_mode_command_105_entity.Reset();
    vehicle_mode_command_105_msg = msg;
    can_vehicle.header.stamp = ros::Time::now();
    can_vehicle.dlc = 8;
    vehicle_mode_command_105_entity.UpdateData(
        vehicle_mode_command_105_msg.Headlight_Ctrl,
	vehicle_mode_command_105_msg.CheckSum_105,
	vehicle_mode_command_105_msg.TurnLight_Ctrl,
	vehicle_mode_command_105_msg.Drive_ModeCtrl,
	vehicle_mode_command_105_msg.Steer_ModeCtrl
    );
    can_vehicle.id = vehicle_mode_command_105_entity.ID;
    can_vehicle.is_extended= false;
    uint8_t *A;
    A = vehicle_mode_command_105_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {
        can_vehicle.data[i] = *A;
        A += 1;
    }
    int t_nsec = 0;
    t_nsec = can_vehicle.header.stamp.toNSec();
    vehicle_prev_t = t_nsec;
}

    
static void acu_callback(const pix_driver_msgs::acu_sweepctrlcmd_107 &msg)
{
    
    acu_sweepctrlcmd_107_entity.Reset();
    acu_sweepctrlcmd_107_msg = msg;
    can_acu.header.stamp = ros::Time::now();
    can_acu.dlc = 8;
    acu_sweepctrlcmd_107_entity.UpdateData(
        acu_sweepctrlcmd_107_msg.FanSpeedCtrl,
	acu_sweepctrlcmd_107_msg.ShakerDusterCtrl,
	acu_sweepctrlcmd_107_msg.DedustingCtrl,
	acu_sweepctrlcmd_107_msg.AutoCleaningStartCtrl,
	acu_sweepctrlcmd_107_msg.AutoGarbageDumpStartCtrl,
	acu_sweepctrlcmd_107_msg.MouthpieceUpDownCtrl,
	acu_sweepctrlcmd_107_msg.SweepPlateUpDown,
	acu_sweepctrlcmd_107_msg.FanModeCtrl,
	acu_sweepctrlcmd_107_msg.FanSpeedMode,
	acu_sweepctrlcmd_107_msg.SweepModeCtrl,
	acu_sweepctrlcmd_107_msg.MowingSpeedCtrl
    );
    can_acu.id = acu_sweepctrlcmd_107_entity.ID;
    can_acu.is_extended= false;
    uint8_t *A;
    A = acu_sweepctrlcmd_107_entity.get_data();
    for(unsigned int i=0;i<8;i++)
    {
        can_acu.data[i] = *A;
        A += 1;
    }
    int t_nsec = 0;
    t_nsec = can_acu.header.stamp.toNSec();
    acu_prev_t = t_nsec;
}

    


//  define timer callback function
void timer_callback(const ros::TimerEvent &te)
{
    int time_diff;
    int now;
    now = ros::Time::now().toNSec();
    /*Example: 
    // brake
    if(now-brake_prev_t>30000000)
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
    
    // throttle
    if(now - throttle_prev_t>30000000)
    {
        for(uint i=0; i<8; i++)
        {   
            can_throttle.id = throttle_command_100_entity.ID;
            can_throttle.data[i] = 0;
        }
        pub_can.publish(can_throttle);
    }
    else{
        pub_can.publish(can_throttle);
    }
    
    // brake
    if(now - brake_prev_t>30000000)
    {
        for(uint i=0; i<8; i++)
        {   
            can_brake.id = brake_command_101_entity.ID;
            can_brake.data[i] = 0;
        }
        pub_can.publish(can_brake);
    }
    else{
        pub_can.publish(can_brake);
    }
    
    // steering
    if(now - steering_prev_t>30000000)
    {
        for(uint i=0; i<8; i++)
        {   
            can_steering.id = steering_command_102_entity.ID;
            can_steering.data[i] = 0;
        }
        pub_can.publish(can_steering);
    }
    else{
        pub_can.publish(can_steering);
    }
    
    // gear
    if(now - gear_prev_t>30000000)
    {
        for(uint i=0; i<8; i++)
        {   
            can_gear.id = gear_command_103_entity.ID;
            can_gear.data[i] = 0;
        }
        pub_can.publish(can_gear);
    }
    else{
        pub_can.publish(can_gear);
    }
    
    // park
    if(now - park_prev_t>30000000)
    {
        for(uint i=0; i<8; i++)
        {   
            can_park.id = park_command_104_entity.ID;
            can_park.data[i] = 0;
        }
        pub_can.publish(can_park);
    }
    else{
        pub_can.publish(can_park);
    }
    
    // vehicle
    if(now - vehicle_prev_t>30000000)
    {
        for(uint i=0; i<8; i++)
        {   
            can_vehicle.id = vehicle_mode_command_105_entity.ID;
            can_vehicle.data[i] = 0;
        }
        pub_can.publish(can_vehicle);
    }
    else{
        pub_can.publish(can_vehicle);
    }
    
    // acu
    if(now - acu_prev_t>30000000)
    {
        for(uint i=0; i<8; i++)
        {   
            can_acu.id = acu_sweepctrlcmd_107_entity.ID;
            can_acu.data[i] = 0;
        }
        pub_can.publish(can_acu);
    }
    else{
        pub_can.publish(can_acu);
    }
    
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "pix_driver_command_node");
    ros::NodeHandle nh;

    // creat ros Subscriber
    // Example: ros::Subscriber sub_brake = nh.subscribe("/pix/brake_command", 1, brake_callback);
    ros::Subscriber sub_throttle = nh.subscribe("/pix/throttle_command", 1, throttle_callback);
	ros::Subscriber sub_brake = nh.subscribe("/pix/brake_command", 1, brake_callback);
	ros::Subscriber sub_steering = nh.subscribe("/pix/steering_command", 1, steering_callback);
	ros::Subscriber sub_gear = nh.subscribe("/pix/gear_command", 1, gear_callback);
	ros::Subscriber sub_park = nh.subscribe("/pix/park_command", 1, park_callback);
	ros::Subscriber sub_vehicle = nh.subscribe("/pix/vehicle_mode_command", 1, vehicle_callback);
	ros::Subscriber sub_acu = nh.subscribe("/pix/acu_sweepctrlcmd", 1, acu_callback);
	
    //  creat ros publisher
    pub_can = nh.advertise<can_msgs::Frame>("/sent_messages", 5, true);

    ros::Timer set_speed = nh.createTimer(ros::Duration(1/50.0), timer_callback);
    ros::spin();

    return 0;

}