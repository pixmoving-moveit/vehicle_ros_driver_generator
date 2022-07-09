/******************************************************************************
 fulongma
 *****************************************************************************/
#include "steering_report_502.hpp"


Steeringreport502::Steeringreport502() {}
int32_t Steeringreport502::ID = 0x502;

void Steeringreport502::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Steeringreport502::Parse() {
  steer_anglerear_actual = SteerAngleRearActual();
  steer_anglespeedactual = SteerAngleSpeedActual();
  steer_flt2 = SteerFlt2();
  steer_flt1 = SteerFlt1();
  steer_enstate = SteerEnState();
  steer_angleactual = SteerAngleActual();
}


// config detail: {'bit': 47, 'is_signed_var': False, 'len': 16, 'name': 'Steer_AngleRear_Actual', 'offset': -500.0, 'order': 'motorola', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
int Steeringreport502::SteerAngleRearActual() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x + -500.000000;
  return ret;
}

// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'Steer_AngleSpeedActual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|250]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
int Steeringreport502::SteerAngleSpeedActual() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 23, 'description': 'Steer system communication fault', 'enum': {0: 'STEER_FLT2_NO_FAULT', 1: 'STEER_FLT2_STEER_SYSTEM_COMUNICATION_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Steer_Flt2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Steeringreport502::SteerFlt2() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 15, 'description': 'Steer system hardware fault', 'enum': {0: 'STEER_FLT1_NO_FAULT', 1: 'STEER_FLT1_STEER_SYSTEM_HARDWARE_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Steer_Flt1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Steeringreport502::SteerFlt1() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'enum': {0: 'STEER_ENSTATE_MANUAL', 1: 'STEER_ENSTATE_AUTO', 2: 'STEER_ENSTATE_TAKEOVER', 3: 'STEER_ENSTATE_STANDBY'}, 'is_signed_var': False, 'len': 2, 'name': 'Steer_EnState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Steeringreport502::SteerEnState() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Steer_AngleActual', 'offset': -500.0, 'order': 'motorola', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
int Steeringreport502::SteerAngleActual() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x + -500.000000;
  return ret;
}

