/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcureport505 {
public:
    static  int32_t ID;
    Vcureport505();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int carwork_state;
    int carpower_state;
    int headlight_actual;
    int aeb_trigger_state;
    int brake_lightactual;
    int turnlight_actual;
    int vehicle_errcode;
    int drive_modestatus;
    int steer_modestatus;
    int vehicle_modestate;
    int vehicle_frontcrashstate;
    int backcrash_state;
    int aeb_brakestate;
    double vehicle_acc;
    double vehicle_speed;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 51, 'enum': {0: 'CARWORK_STATE_INIT', 1: 'CARWORK_STATE_1', 2: 'CARWORK_STATE_2', 3: 'CARWORK_STATE_3', 4: 'CARWORK_STATE_WORK', 5: 'CARWORK_STATE_E_STOP', 6: 'CARWORK_STATE_ERROR', 7: 'CARWORK_STATE_CRASH'}, 'is_signed_var': False, 'len': 4, 'name': 'CarWork_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int CarWorkState();

  // config detail: {'bit': 53, 'enum': {0: 'CARPOWER_STATE_OFF', 1: 'CARPOWER_STATE_ON', 2: 'CARPOWER_STATE_READY'}, 'is_signed_var': False, 'len': 2, 'name': 'CarPower_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int CarPowerState();

  // config detail: {'bit': 59, 'enum': {0: 'HEADLIGHT_ACTUAL_OFF', 1: 'HEADLIGHT_ACTUAL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'Headlight_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int HeadlightActual();

  // config detail: {'bit': 58, 'enum': {0: 'AEB_TRIGGER_STATE_NOTRIGGER', 1: 'AEB_TRIGGER_STATE_FRONTTRIGGER', 2: 'AEB_TRIGGER_STATE_BACKTRIGGER', 4: 'AEB_TRIGGER_STATE_LEFTTRIGGER', 8: 'AEB_TRIGGER_STATE_RIGHTTRIGGER'}, 'is_signed_var': False, 'len': 1, 'name': 'AEB_Trigger_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int AEBTriggerState();

  // config detail: {'bit': 11, 'enum': {0: 'BRAKE_LIGHTACTUAL_BRAKELIGHT_OFF', 1: 'BRAKE_LIGHTACTUAL_BRAKELIGHT_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'Brake_LightActual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int BrakeLightActual();

  // config detail: {'bit': 57, 'enum': {0: 'TURNLIGHT_ACTUAL_TURNLAMPSTS_OFF', 1: 'TURNLIGHT_ACTUAL_LEFT_TURNLAMPSTS_ON', 2: 'TURNLIGHT_ACTUAL_RIGHT_TURNLAMPSTS_ON', 3: 'TURNLIGHT_ACTUAL_HAZARD_WARNING_LAMPSTS_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'TurnLight_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int TurnLightActual();

  // config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'Vehicle_Errcode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int VehicleErrcode();

  // config detail: {'bit': 39, 'enum': {0: 'DRIVE_MODESTATUS_THROTTLE_PADDLE_DRIVE_MODE', 1: 'DRIVE_MODESTATUS_SPEED_DRIVE_MODE'}, 'is_signed_var': False, 'len': 3, 'name': 'Drive_ModeStatus', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int DriveModeStatus();

  // config detail: {'bit': 10, 'enum': {0: 'STEER_MODESTATUS_STANDARD_STEER_MODE', 1: 'STEER_MODESTATUS_NON_DIRECTION_STEER_MODE', 2: 'STEER_MODESTATUS_SYNC_DIRECTION_STEER_MODE'}, 'is_signed_var': False, 'len': 3, 'name': 'Steer_ModeStatus', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int SteerModeStatus();

  // config detail: {'bit': 36, 'enum': {0: 'VEHICLE_MODESTATE_MANUAL_REMOTE_MODE', 1: 'VEHICLE_MODESTATE_AUTO_MODE', 2: 'VEHICLE_MODESTATE_EMERGENCY_MODE', 3: 'VEHICLE_MODESTATE_STANDBY_MODE'}, 'is_signed_var': False, 'len': 2, 'name': 'Vehicle_ModeState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int VehicleModeState();

  // config detail: {'bit': 33, 'enum': {0: 'VEHICLE_FRONTCRASHSTATE_NO_EVENT', 1: 'VEHICLE_FRONTCRASHSTATE_CRASH_EVENT'}, 'is_signed_var': False, 'len': 1, 'name': 'Vehicle_FrontCrashState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int VehicleFrontCrashState();

  // config detail: {'bit': 34, 'enum': {0: 'BACKCRASH_STATE_NO_EVENT', 1: 'BACKCRASH_STATE_CRASH_EVENT'}, 'is_signed_var': False, 'len': 1, 'name': 'BackCrash_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int BackCrashState();

  // config detail: {'bit': 32, 'enum': {0: 'AEB_BRAKESTATE_INACTIVE', 1: 'AEB_BRAKESTATE_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'AEB_BrakeState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int AEBBrakeState();

  // config detail: {'bit': 7, 'is_signed_var': True, 'len': 12, 'name': 'Vehicle_Acc', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-10|10]', 'physical_unit': 'm/s^2', 'precision': 0.01, 'type': 'double'}
  double VehicleAcc();

  // config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Vehicle_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-32.768|32.767]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
  double VehicleSpeed();
};



