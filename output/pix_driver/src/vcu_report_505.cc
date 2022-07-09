/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu_report_505.hpp"


Vcureport505::Vcureport505() {}
int32_t Vcureport505::ID = 0x505;

void Vcureport505::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcureport505::Parse() {
  carwork_state = CarWorkState();
  carpower_state = CarPowerState();
  headlight_actual = HeadlightActual();
  aeb_trigger_state = AEBTriggerState();
  brake_lightactual = BrakeLightActual();
  turnlight_actual = TurnLightActual();
  vehicle_errcode = VehicleErrcode();
  drive_modestatus = DriveModeStatus();
  steer_modestatus = SteerModeStatus();
  vehicle_modestate = VehicleModeState();
  vehicle_frontcrashstate = VehicleFrontCrashState();
  backcrash_state = BackCrashState();
  aeb_brakestate = AEBBrakeState();
  vehicle_acc = VehicleAcc();
  vehicle_speed = VehicleSpeed();
}


// config detail: {'bit': 51, 'enum': {0: 'CARWORK_STATE_INIT', 1: 'CARWORK_STATE_1', 2: 'CARWORK_STATE_2', 3: 'CARWORK_STATE_3', 4: 'CARWORK_STATE_WORK', 5: 'CARWORK_STATE_E_STOP', 6: 'CARWORK_STATE_ERROR', 7: 'CARWORK_STATE_CRASH'}, 'is_signed_var': False, 'len': 4, 'name': 'CarWork_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::CarWorkState() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 53, 'enum': {0: 'CARPOWER_STATE_OFF', 1: 'CARPOWER_STATE_ON', 2: 'CARPOWER_STATE_READY'}, 'is_signed_var': False, 'len': 2, 'name': 'CarPower_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::CarPowerState() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 59, 'enum': {0: 'HEADLIGHT_ACTUAL_OFF', 1: 'HEADLIGHT_ACTUAL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'Headlight_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::HeadlightActual() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 58, 'enum': {0: 'AEB_TRIGGER_STATE_NOTRIGGER', 1: 'AEB_TRIGGER_STATE_FRONTTRIGGER', 2: 'AEB_TRIGGER_STATE_BACKTRIGGER', 4: 'AEB_TRIGGER_STATE_LEFTTRIGGER', 8: 'AEB_TRIGGER_STATE_RIGHTTRIGGER'}, 'is_signed_var': False, 'len': 1, 'name': 'AEB_Trigger_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::AEBTriggerState() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 11, 'enum': {0: 'BRAKE_LIGHTACTUAL_BRAKELIGHT_OFF', 1: 'BRAKE_LIGHTACTUAL_BRAKELIGHT_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'Brake_LightActual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::BrakeLightActual() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 57, 'enum': {0: 'TURNLIGHT_ACTUAL_TURNLAMPSTS_OFF', 1: 'TURNLIGHT_ACTUAL_LEFT_TURNLAMPSTS_ON', 2: 'TURNLIGHT_ACTUAL_RIGHT_TURNLAMPSTS_ON', 3: 'TURNLIGHT_ACTUAL_HAZARD_WARNING_LAMPSTS_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'TurnLight_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::TurnLightActual() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'Vehicle_Errcode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcureport505::VehicleErrcode() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 39, 'enum': {0: 'DRIVE_MODESTATUS_THROTTLE_PADDLE_DRIVE_MODE', 1: 'DRIVE_MODESTATUS_SPEED_DRIVE_MODE'}, 'is_signed_var': False, 'len': 3, 'name': 'Drive_ModeStatus', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::DriveModeStatus() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(5, 3);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 10, 'enum': {0: 'STEER_MODESTATUS_STANDARD_STEER_MODE', 1: 'STEER_MODESTATUS_NON_DIRECTION_STEER_MODE', 2: 'STEER_MODESTATUS_SYNC_DIRECTION_STEER_MODE'}, 'is_signed_var': False, 'len': 3, 'name': 'Steer_ModeStatus', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::SteerModeStatus() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 3);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 36, 'enum': {0: 'VEHICLE_MODESTATE_MANUAL_REMOTE_MODE', 1: 'VEHICLE_MODESTATE_AUTO_MODE', 2: 'VEHICLE_MODESTATE_EMERGENCY_MODE', 3: 'VEHICLE_MODESTATE_STANDBY_MODE'}, 'is_signed_var': False, 'len': 2, 'name': 'Vehicle_ModeState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::VehicleModeState() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(3, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 33, 'enum': {0: 'VEHICLE_FRONTCRASHSTATE_NO_EVENT', 1: 'VEHICLE_FRONTCRASHSTATE_CRASH_EVENT'}, 'is_signed_var': False, 'len': 1, 'name': 'Vehicle_FrontCrashState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::VehicleFrontCrashState() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 34, 'enum': {0: 'BACKCRASH_STATE_NO_EVENT', 1: 'BACKCRASH_STATE_CRASH_EVENT'}, 'is_signed_var': False, 'len': 1, 'name': 'BackCrash_State', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::BackCrashState() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'enum': {0: 'AEB_BRAKESTATE_INACTIVE', 1: 'AEB_BRAKESTATE_ACTIVE'}, 'is_signed_var': False, 'len': 1, 'name': 'AEB_BrakeState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcureport505::AEBBrakeState() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'is_signed_var': True, 'len': 12, 'name': 'Vehicle_Acc', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-10|10]', 'physical_unit': 'm/s^2', 'precision': 0.01, 'type': 'double'}
double Vcureport505::VehicleAcc() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(4, 4);
  x <<= 4;
  x |= t;

  x <<= 20;
  x >>= 20;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': True, 'len': 16, 'name': 'Vehicle_Speed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[-32.768|32.767]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
double Vcureport505::VehicleSpeed() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 3));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  double ret = x * 0.001000;
  return ret;
}

