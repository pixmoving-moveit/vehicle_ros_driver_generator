#include <math.h>
#include <iostream>
#include "ros/ros.h"
#include "can_msgs/Frame.h"
#include "std_msgs/Header.h"

// name = 
// # include "pix pix_driver_msgs/{name}.h"
#include "pix_driver_msgs/vcu2acu_chassiserrcode1_200.h"
#include "pix_driver_msgs/vcu2acu_chassiserrcode2_201.h"
#include "pix_driver_msgs/vcu2acu_chassiserrcode3_202.h"
#include "pix_driver_msgs/throttle_report_500.h"
#include "pix_driver_msgs/brake_report_501.h"
#include "pix_driver_msgs/steering_report_502.h"
#include "pix_driver_msgs/gear_report_503.h"
#include "pix_driver_msgs/park_report_504.h"
#include "pix_driver_msgs/vcu_report_505.h"
#include "pix_driver_msgs/wheelspeed_report_506.h"
#include "pix_driver_msgs/bms_report_512.h"
#include "pix_driver_msgs/vcu2acu_sweepstafb_517.h"
#include "pix_driver_msgs/vcu2acu_sweepfansta_518.h"
#include "pix_driver_msgs/vcu2acu_sweepsta_519.h"
#include "pix_driver_msgs/vcu2acu_sweepweedingsta_520.h"
#include "pix_driver_msgs/vcu2acu_sweepworksta_521.h"


// # include "{name}.hpp"
#include "vcu2acu_chassiserrcode1_200.hpp"
#include "vcu2acu_chassiserrcode2_201.hpp"
#include "vcu2acu_chassiserrcode3_202.hpp"
#include "throttle_report_500.hpp"
#include "brake_report_501.hpp"
#include "steering_report_502.hpp"
#include "gear_report_503.hpp"
#include "park_report_504.hpp"
#include "vcu_report_505.hpp"
#include "wheelspeed_report_506.hpp"
#include "bms_report_512.hpp"
#include "vcu2acu_sweepstafb_517.hpp"
#include "vcu2acu_sweepfansta_518.hpp"
#include "vcu2acu_sweepsta_519.hpp"
#include "vcu2acu_sweepweedingsta_520.hpp"
#include "vcu2acu_sweepworksta_521.hpp"


static can_msgs::Frame can_frame_msg;

// static ros::Publisher pub_{can_name};
static ros::Publisher pub_vcu2acu_chassiserrcode1;
static ros::Publisher pub_vcu2acu_chassiserrcode2;
static ros::Publisher pub_vcu2acu_chassiserrcode3;
static ros::Publisher pub_throttle_report;
static ros::Publisher pub_brake_report;
static ros::Publisher pub_steering_report;
static ros::Publisher pub_gear_report;
static ros::Publisher pub_park_report;
static ros::Publisher pub_vcu_report;
static ros::Publisher pub_wheelspeed_report;
static ros::Publisher pub_bms_report;
static ros::Publisher pub_vcu2acu_sweepstafb;
static ros::Publisher pub_vcu2acu_sweepfansta;
static ros::Publisher pub_vcu2acu_sweepsta;
static ros::Publisher pub_vcu2acu_sweepweedingsta;
static ros::Publisher pub_vcu2acu_sweepworksta;


// static pix_driver_msgs::{name} {name}_msg;
static pix_driver_msgs::vcu2acu_chassiserrcode1_200 vcu2acu_chassiserrcode1_200_msg;
static pix_driver_msgs::vcu2acu_chassiserrcode2_201 vcu2acu_chassiserrcode2_201_msg;
static pix_driver_msgs::vcu2acu_chassiserrcode3_202 vcu2acu_chassiserrcode3_202_msg;
static pix_driver_msgs::throttle_report_500 throttle_report_500_msg;
static pix_driver_msgs::brake_report_501 brake_report_501_msg;
static pix_driver_msgs::steering_report_502 steering_report_502_msg;
static pix_driver_msgs::gear_report_503 gear_report_503_msg;
static pix_driver_msgs::park_report_504 park_report_504_msg;
static pix_driver_msgs::vcu_report_505 vcu_report_505_msg;
static pix_driver_msgs::wheelspeed_report_506 wheelspeed_report_506_msg;
static pix_driver_msgs::bms_report_512 bms_report_512_msg;
static pix_driver_msgs::vcu2acu_sweepstafb_517 vcu2acu_sweepstafb_517_msg;
static pix_driver_msgs::vcu2acu_sweepfansta_518 vcu2acu_sweepfansta_518_msg;
static pix_driver_msgs::vcu2acu_sweepsta_519 vcu2acu_sweepsta_519_msg;
static pix_driver_msgs::vcu2acu_sweepweedingsta_520 vcu2acu_sweepweedingsta_520_msg;
static pix_driver_msgs::vcu2acu_sweepworksta_521 vcu2acu_sweepworksta_521_msg;


// static {name}.replace('_', '').capitalize()  {name}_entity
static Vcu2acuchassiserrcode1200  vcu2acu_chassiserrcode1_200_entity;
static Vcu2acuchassiserrcode2201  vcu2acu_chassiserrcode2_201_entity;
static Vcu2acuchassiserrcode3202  vcu2acu_chassiserrcode3_202_entity;
static Throttlereport500  throttle_report_500_entity;
static Brakereport501  brake_report_501_entity;
static Steeringreport502  steering_report_502_entity;
static Gearreport503  gear_report_503_entity;
static Parkreport504  park_report_504_entity;
static Vcureport505  vcu_report_505_entity;
static Wheelspeedreport506  wheelspeed_report_506_entity;
static Bmsreport512  bms_report_512_entity;
static Vcu2acusweepstafb517  vcu2acu_sweepstafb_517_entity;
static Vcu2acusweepfansta518  vcu2acu_sweepfansta_518_entity;
static Vcu2acusweepsta519  vcu2acu_sweepsta_519_entity;
static Vcu2acusweepweedingsta520  vcu2acu_sweepweedingsta_520_entity;
static Vcu2acusweepworksta521  vcu2acu_sweepworksta_521_entity;



// callback func
static void can_callback(const can_msgs::Frame &msg)
{
    can_frame_msg = msg;
    std_msgs::Header header;
    header.frame_id = "pix";
    header.stamp = can_frame_msg.header.stamp;
    
    if(can_frame_msg.id==vcu2acu_chassiserrcode1_200_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_chassiserrcode1_200_entity.update_bytes(byte_temp);
        vcu2acu_chassiserrcode1_200_entity.Parse();
        vcu2acu_chassiserrcode1_200_msg.header = header;
		vcu2acu_chassiserrcode1_200_msg.BMS_CommunicationFault = vcu2acu_chassiserrcode1_200_entity.bms_communicationfault;
		vcu2acu_chassiserrcode1_200_msg.ChassisEmergencySta = vcu2acu_chassiserrcode1_200_entity.chassisemergencysta;
		vcu2acu_chassiserrcode1_200_msg.LeadacidBatteryLow = vcu2acu_chassiserrcode1_200_entity.leadacidbatterylow;
		vcu2acu_chassiserrcode1_200_msg.ControlerCommunicationFault = vcu2acu_chassiserrcode1_200_entity.controlercommunicationfault;
		vcu2acu_chassiserrcode1_200_msg.ChassisCrashSta = vcu2acu_chassiserrcode1_200_entity.chassiscrashsta;
		vcu2acu_chassiserrcode1_200_msg.EPS_RearCommunicationFault = vcu2acu_chassiserrcode1_200_entity.eps_rearcommunicationfault;
		vcu2acu_chassiserrcode1_200_msg.EPS_FrontCommunicationFault = vcu2acu_chassiserrcode1_200_entity.eps_frontcommunicationfault;
		vcu2acu_chassiserrcode1_200_msg.EDS_RrCommunicationFault = vcu2acu_chassiserrcode1_200_entity.eds_rrcommunicationfault;
		vcu2acu_chassiserrcode1_200_msg.EDS_RfCommunicationFault = vcu2acu_chassiserrcode1_200_entity.eds_rfcommunicationfault;
		vcu2acu_chassiserrcode1_200_msg.EDS_LrCommunicationFault = vcu2acu_chassiserrcode1_200_entity.eds_lrcommunicationfault;
		vcu2acu_chassiserrcode1_200_msg.EDS_LfCommunicationFault = vcu2acu_chassiserrcode1_200_entity.eds_lfcommunicationfault;
		vcu2acu_chassiserrcode1_200_msg.EBS_CommunicationFault = vcu2acu_chassiserrcode1_200_entity.ebs_communicationfault;
		vcu2acu_chassiserrcode1_200_msg.ChassisVcuOtherErr = vcu2acu_chassiserrcode1_200_entity.chassisvcuothererr;

        pub_vcu2acu_chassiserrcode1.publish(vcu2acu_chassiserrcode1_200_msg);
    }
    
    if(can_frame_msg.id==vcu2acu_chassiserrcode2_201_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_chassiserrcode2_201_entity.update_bytes(byte_temp);
        vcu2acu_chassiserrcode2_201_entity.Parse();
        vcu2acu_chassiserrcode2_201_msg.header = header;
		vcu2acu_chassiserrcode2_201_msg.ChassisEbsErrorCode3 = vcu2acu_chassiserrcode2_201_entity.chassisebserrorcode3;
		vcu2acu_chassiserrcode2_201_msg.ChassisBmsErrorCode = vcu2acu_chassiserrcode2_201_entity.chassisbmserrorcode;
		vcu2acu_chassiserrcode2_201_msg.ChassisBackEpsErrorCode = vcu2acu_chassiserrcode2_201_entity.chassisbackepserrorcode;
		vcu2acu_chassiserrcode2_201_msg.ChassisFrontEpsErrorCode = vcu2acu_chassiserrcode2_201_entity.chassisfrontepserrorcode;
		vcu2acu_chassiserrcode2_201_msg.ChassisEbsErrorCode2 = vcu2acu_chassiserrcode2_201_entity.chassisebserrorcode2;
		vcu2acu_chassiserrcode2_201_msg.ChassisEbsErrorCode1 = vcu2acu_chassiserrcode2_201_entity.chassisebserrorcode1;

        pub_vcu2acu_chassiserrcode2.publish(vcu2acu_chassiserrcode2_201_msg);
    }
    
    if(can_frame_msg.id==vcu2acu_chassiserrcode3_202_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_chassiserrcode3_202_entity.update_bytes(byte_temp);
        vcu2acu_chassiserrcode3_202_entity.Parse();
        vcu2acu_chassiserrcode3_202_msg.header = header;
		vcu2acu_chassiserrcode3_202_msg.ChassisRrEdsErrorCode2 = vcu2acu_chassiserrcode3_202_entity.chassisrredserrorcode2;
		vcu2acu_chassiserrcode3_202_msg.ChassisRfEdsErrorCode2 = vcu2acu_chassiserrcode3_202_entity.chassisrfedserrorcode2;
		vcu2acu_chassiserrcode3_202_msg.ChassisLrEdsErrorCode2 = vcu2acu_chassiserrcode3_202_entity.chassislredserrorcode2;
		vcu2acu_chassiserrcode3_202_msg.ChassisLfEdsErrorCode2 = vcu2acu_chassiserrcode3_202_entity.chassislfedserrorcode2;
		vcu2acu_chassiserrcode3_202_msg.ChassisRrEdsErrorCode = vcu2acu_chassiserrcode3_202_entity.chassisrredserrorcode;
		vcu2acu_chassiserrcode3_202_msg.ChassisRfEdsErrorCode = vcu2acu_chassiserrcode3_202_entity.chassisrfedserrorcode;
		vcu2acu_chassiserrcode3_202_msg.ChassisLrEdsErrorCode = vcu2acu_chassiserrcode3_202_entity.chassislredserrorcode;
		vcu2acu_chassiserrcode3_202_msg.ChassisLfEdsErrorCode = vcu2acu_chassiserrcode3_202_entity.chassislfedserrorcode;

        pub_vcu2acu_chassiserrcode3.publish(vcu2acu_chassiserrcode3_202_msg);
    }
    
    if(can_frame_msg.id==throttle_report_500_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        throttle_report_500_entity.update_bytes(byte_temp);
        throttle_report_500_entity.Parse();
        throttle_report_500_msg.header = header;
		throttle_report_500_msg.Dirve_ThrottlePedalActual = throttle_report_500_entity.dirve_throttlepedalactual;
		throttle_report_500_msg.Dirve_Flt2 = throttle_report_500_entity.dirve_flt2;
		throttle_report_500_msg.Dirve_Flt1 = throttle_report_500_entity.dirve_flt1;
		throttle_report_500_msg.Dirve_EnState = throttle_report_500_entity.dirve_enstate;

        pub_throttle_report.publish(throttle_report_500_msg);
    }
    
    if(can_frame_msg.id==brake_report_501_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        brake_report_501_entity.update_bytes(byte_temp);
        brake_report_501_entity.Parse();
        brake_report_501_msg.header = header;
		brake_report_501_msg.Brake_PedalActual = brake_report_501_entity.brake_pedalactual;
		brake_report_501_msg.Brake_Flt2 = brake_report_501_entity.brake_flt2;
		brake_report_501_msg.Brake_Flt1 = brake_report_501_entity.brake_flt1;
		brake_report_501_msg.Brake_EnState = brake_report_501_entity.brake_enstate;

        pub_brake_report.publish(brake_report_501_msg);
    }
    
    if(can_frame_msg.id==steering_report_502_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        steering_report_502_entity.update_bytes(byte_temp);
        steering_report_502_entity.Parse();
        steering_report_502_msg.header = header;
		steering_report_502_msg.Steer_AngleRear_Actual = steering_report_502_entity.steer_anglerear_actual;
		steering_report_502_msg.Steer_AngleSpeedActual = steering_report_502_entity.steer_anglespeedactual;
		steering_report_502_msg.Steer_Flt2 = steering_report_502_entity.steer_flt2;
		steering_report_502_msg.Steer_Flt1 = steering_report_502_entity.steer_flt1;
		steering_report_502_msg.Steer_EnState = steering_report_502_entity.steer_enstate;
		steering_report_502_msg.Steer_AngleActual = steering_report_502_entity.steer_angleactual;

        pub_steering_report.publish(steering_report_502_msg);
    }
    
    if(can_frame_msg.id==gear_report_503_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        gear_report_503_entity.update_bytes(byte_temp);
        gear_report_503_entity.Parse();
        gear_report_503_msg.header = header;
		gear_report_503_msg.Gear_Flt = gear_report_503_entity.gear_flt;
		gear_report_503_msg.Gear_Actual = gear_report_503_entity.gear_actual;

        pub_gear_report.publish(gear_report_503_msg);
    }
    
    if(can_frame_msg.id==park_report_504_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        park_report_504_entity.update_bytes(byte_temp);
        park_report_504_entity.Parse();
        park_report_504_msg.header = header;
		park_report_504_msg.Parking_Actual = park_report_504_entity.parking_actual;
		park_report_504_msg.Park_Flt = park_report_504_entity.park_flt;

        pub_park_report.publish(park_report_504_msg);
    }
    
    if(can_frame_msg.id==vcu_report_505_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu_report_505_entity.update_bytes(byte_temp);
        vcu_report_505_entity.Parse();
        vcu_report_505_msg.header = header;
		vcu_report_505_msg.CarWork_State = vcu_report_505_entity.carwork_state;
		vcu_report_505_msg.CarPower_State = vcu_report_505_entity.carpower_state;
		vcu_report_505_msg.Headlight_Actual = vcu_report_505_entity.headlight_actual;
		vcu_report_505_msg.AEB_Trigger_State = vcu_report_505_entity.aeb_trigger_state;
		vcu_report_505_msg.Brake_LightActual = vcu_report_505_entity.brake_lightactual;
		vcu_report_505_msg.TurnLight_Actual = vcu_report_505_entity.turnlight_actual;
		vcu_report_505_msg.Vehicle_Errcode = vcu_report_505_entity.vehicle_errcode;
		vcu_report_505_msg.Drive_ModeStatus = vcu_report_505_entity.drive_modestatus;
		vcu_report_505_msg.Steer_ModeStatus = vcu_report_505_entity.steer_modestatus;
		vcu_report_505_msg.Vehicle_ModeState = vcu_report_505_entity.vehicle_modestate;
		vcu_report_505_msg.Vehicle_FrontCrashState = vcu_report_505_entity.vehicle_frontcrashstate;
		vcu_report_505_msg.BackCrash_State = vcu_report_505_entity.backcrash_state;
		vcu_report_505_msg.AEB_BrakeState = vcu_report_505_entity.aeb_brakestate;
		vcu_report_505_msg.Vehicle_Acc = vcu_report_505_entity.vehicle_acc;
		vcu_report_505_msg.Vehicle_Speed = vcu_report_505_entity.vehicle_speed;

        pub_vcu_report.publish(vcu_report_505_msg);
    }
    
    if(can_frame_msg.id==wheelspeed_report_506_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        wheelspeed_report_506_entity.update_bytes(byte_temp);
        wheelspeed_report_506_entity.Parse();
        wheelspeed_report_506_msg.header = header;
		wheelspeed_report_506_msg.WheelSpeedRR = wheelspeed_report_506_entity.wheelspeedrr;
		wheelspeed_report_506_msg.WheelSpeedRL = wheelspeed_report_506_entity.wheelspeedrl;
		wheelspeed_report_506_msg.WheelSpeedFR = wheelspeed_report_506_entity.wheelspeedfr;
		wheelspeed_report_506_msg.WheelSpeedFL = wheelspeed_report_506_entity.wheelspeedfl;

        pub_wheelspeed_report.publish(wheelspeed_report_506_msg);
    }
    
    if(can_frame_msg.id==bms_report_512_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        bms_report_512_entity.update_bytes(byte_temp);
        bms_report_512_entity.Parse();
        bms_report_512_msg.header = header;
		bms_report_512_msg.WirelessCharging_Sta = bms_report_512_entity.wirelesscharging_sta;
		bms_report_512_msg.BatteryLeadacid_Voltage = bms_report_512_entity.batteryleadacid_voltage;
		bms_report_512_msg.Battery_Current = bms_report_512_entity.battery_current;
		bms_report_512_msg.Battery_Voltage = bms_report_512_entity.battery_voltage;
		bms_report_512_msg.Battery_Soc = bms_report_512_entity.battery_soc;

        pub_bms_report.publish(bms_report_512_msg);
    }
    
    if(can_frame_msg.id==vcu2acu_sweepstafb_517_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_sweepstafb_517_entity.update_bytes(byte_temp);
        vcu2acu_sweepstafb_517_entity.Parse();
        vcu2acu_sweepstafb_517_msg.header = header;
		vcu2acu_sweepstafb_517_msg.SCU_SweepLifeEnd = vcu2acu_sweepstafb_517_entity.scu_sweeplifeend;
		vcu2acu_sweepstafb_517_msg.SCU_FilterClogging = vcu2acu_sweepstafb_517_entity.scu_filterclogging;
		vcu2acu_sweepstafb_517_msg.SCU_LiquidLevelLow = vcu2acu_sweepstafb_517_entity.scu_liquidlevellow;
		vcu2acu_sweepstafb_517_msg.SCU_LiquidLeveHigh = vcu2acu_sweepstafb_517_entity.scu_liquidlevehigh;
		vcu2acu_sweepstafb_517_msg.SCU_LiquidLeve = vcu2acu_sweepstafb_517_entity.scu_liquidleve;
		vcu2acu_sweepstafb_517_msg.SCU_DustbinFull = vcu2acu_sweepstafb_517_entity.scu_dustbinfull;
		vcu2acu_sweepstafb_517_msg.SCU_Heartbeat = vcu2acu_sweepstafb_517_entity.scu_heartbeat;
		vcu2acu_sweepstafb_517_msg.SCU_FanSpeedFb = vcu2acu_sweepstafb_517_entity.scu_fanspeedfb;
		vcu2acu_sweepstafb_517_msg.SCU_MowingSpeedFb = vcu2acu_sweepstafb_517_entity.scu_mowingspeedfb;
		vcu2acu_sweepstafb_517_msg.SCU_SweepSpeedFb = vcu2acu_sweepstafb_517_entity.scu_sweepspeedfb;

        pub_vcu2acu_sweepstafb.publish(vcu2acu_sweepstafb_517_msg);
    }
    
    if(can_frame_msg.id==vcu2acu_sweepfansta_518_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_sweepfansta_518_entity.update_bytes(byte_temp);
        vcu2acu_sweepfansta_518_entity.Parse();
        vcu2acu_sweepfansta_518_msg.header = header;
		vcu2acu_sweepfansta_518_msg.SCU_FanConntorllerMainVoltage = vcu2acu_sweepfansta_518_entity.scu_fanconntorllermainvoltage;
		vcu2acu_sweepfansta_518_msg.SCU_FanConntorllerCurrent = vcu2acu_sweepfansta_518_entity.scu_fanconntorllercurrent;
		vcu2acu_sweepfansta_518_msg.SCU_FanMotorTemp = vcu2acu_sweepfansta_518_entity.scu_fanmotortemp;
		vcu2acu_sweepfansta_518_msg.SCU_FanConntorllerTemp = vcu2acu_sweepfansta_518_entity.scu_fanconntorllertemp;
		vcu2acu_sweepfansta_518_msg.SCU_FanConntorllerErr1 = vcu2acu_sweepfansta_518_entity.scu_fanconntorllererr1;
		vcu2acu_sweepfansta_518_msg.SCU_FanConntorllerErr2 = vcu2acu_sweepfansta_518_entity.scu_fanconntorllererr2;

        pub_vcu2acu_sweepfansta.publish(vcu2acu_sweepfansta_518_msg);
    }
    
    if(can_frame_msg.id==vcu2acu_sweepsta_519_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_sweepsta_519_entity.update_bytes(byte_temp);
        vcu2acu_sweepsta_519_entity.Parse();
        vcu2acu_sweepsta_519_msg.header = header;
		vcu2acu_sweepsta_519_msg.SCU_SweepTravel_mm = vcu2acu_sweepsta_519_entity.scu_sweeptravel_mm;
		vcu2acu_sweepsta_519_msg.SCU_SweepSpeed = vcu2acu_sweepsta_519_entity.scu_sweepspeed;
		vcu2acu_sweepsta_519_msg.SCU_SweepConntrollerVoltage = vcu2acu_sweepsta_519_entity.scu_sweepconntrollervoltage;
		vcu2acu_sweepsta_519_msg.SCU_SweepConntrollerCurrent = vcu2acu_sweepsta_519_entity.scu_sweepconntrollercurrent;
		vcu2acu_sweepsta_519_msg.SCU_SweepConntorllerErr1 = vcu2acu_sweepsta_519_entity.scu_sweepconntorllererr1;
		vcu2acu_sweepsta_519_msg.SCU_SweepConntorllerErr2 = vcu2acu_sweepsta_519_entity.scu_sweepconntorllererr2;

        pub_vcu2acu_sweepsta.publish(vcu2acu_sweepsta_519_msg);
    }
    
    if(can_frame_msg.id==vcu2acu_sweepweedingsta_520_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_sweepweedingsta_520_entity.update_bytes(byte_temp);
        vcu2acu_sweepweedingsta_520_entity.Parse();
        vcu2acu_sweepweedingsta_520_msg.header = header;
		vcu2acu_sweepweedingsta_520_msg.SCU_WeedingSta = vcu2acu_sweepweedingsta_520_entity.scu_weedingsta;

        pub_vcu2acu_sweepweedingsta.publish(vcu2acu_sweepweedingsta_520_msg);
    }
    
    if(can_frame_msg.id==vcu2acu_sweepworksta_521_entity.ID)
    {
        uint8_t byte_temp[8];
        for(uint i=0;i<8;i++)
        {
        byte_temp[i] = can_frame_msg.data[i];
        }
        vcu2acu_sweepworksta_521_entity.update_bytes(byte_temp);
        vcu2acu_sweepworksta_521_entity.Parse();
        vcu2acu_sweepworksta_521_msg.header = header;
		vcu2acu_sweepworksta_521_msg.SweepEmergencySigFb = vcu2acu_sweepworksta_521_entity.sweepemergencysigfb;
		vcu2acu_sweepworksta_521_msg.VCU_SweepPlateUpDownStaFb = vcu2acu_sweepworksta_521_entity.vcu_sweepplateupdownstafb;
		vcu2acu_sweepworksta_521_msg.VCU_AutoGarbageDumpStaFb = vcu2acu_sweepworksta_521_entity.vcu_autogarbagedumpstafb;
		vcu2acu_sweepworksta_521_msg.VCU_AutoCleaningStaFb = vcu2acu_sweepworksta_521_entity.vcu_autocleaningstafb;

        pub_vcu2acu_sweepworksta.publish(vcu2acu_sweepworksta_521_msg);
    }
    
}


int main(int argc, char* argv[])
{
    ros::init(argc, argv, "pix_driver_report_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/received_messages", 1, can_callback);

    // pub_{can_name} = nh.advertise<pix_driver_msgs::{name}>("/pix/{can_name}_report", 1, true);
    pub_vcu2acu_chassiserrcode1 = nh.advertise<pix_driver_msgs::vcu2acu_chassiserrcode1_200>("/pix/vcu2acu_chassiserrcode1", 1, true);
	pub_vcu2acu_chassiserrcode2 = nh.advertise<pix_driver_msgs::vcu2acu_chassiserrcode2_201>("/pix/vcu2acu_chassiserrcode2", 1, true);
	pub_vcu2acu_chassiserrcode3 = nh.advertise<pix_driver_msgs::vcu2acu_chassiserrcode3_202>("/pix/vcu2acu_chassiserrcode3", 1, true);
	pub_throttle_report = nh.advertise<pix_driver_msgs::throttle_report_500>("/pix/throttle_report", 1, true);
	pub_brake_report = nh.advertise<pix_driver_msgs::brake_report_501>("/pix/brake_report", 1, true);
	pub_steering_report = nh.advertise<pix_driver_msgs::steering_report_502>("/pix/steering_report", 1, true);
	pub_gear_report = nh.advertise<pix_driver_msgs::gear_report_503>("/pix/gear_report", 1, true);
	pub_park_report = nh.advertise<pix_driver_msgs::park_report_504>("/pix/park_report", 1, true);
	pub_vcu_report = nh.advertise<pix_driver_msgs::vcu_report_505>("/pix/vcu_report", 1, true);
	pub_wheelspeed_report = nh.advertise<pix_driver_msgs::wheelspeed_report_506>("/pix/wheelspeed_report", 1, true);
	pub_bms_report = nh.advertise<pix_driver_msgs::bms_report_512>("/pix/bms_report", 1, true);
	pub_vcu2acu_sweepstafb = nh.advertise<pix_driver_msgs::vcu2acu_sweepstafb_517>("/pix/vcu2acu_sweepstafb", 1, true);
	pub_vcu2acu_sweepfansta = nh.advertise<pix_driver_msgs::vcu2acu_sweepfansta_518>("/pix/vcu2acu_sweepfansta", 1, true);
	pub_vcu2acu_sweepsta = nh.advertise<pix_driver_msgs::vcu2acu_sweepsta_519>("/pix/vcu2acu_sweepsta", 1, true);
	pub_vcu2acu_sweepweedingsta = nh.advertise<pix_driver_msgs::vcu2acu_sweepweedingsta_520>("/pix/vcu2acu_sweepweedingsta", 1, true);
	pub_vcu2acu_sweepworksta = nh.advertise<pix_driver_msgs::vcu2acu_sweepworksta_521>("/pix/vcu2acu_sweepworksta", 1, true);
	
    // add another publisher

    ros::spin();
    return 0;

}
