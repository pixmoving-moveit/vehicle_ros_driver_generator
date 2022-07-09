/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Steeringreport502 {
public:
    static  int32_t ID;
    Steeringreport502();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int steer_anglerear_actual;
    int steer_anglespeedactual;
    int steer_flt2;
    int steer_flt1;
    int steer_enstate;
    int steer_angleactual;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 47, 'is_signed_var': False, 'len': 16, 'name': 'Steer_AngleRear_Actual', 'offset': -500.0, 'order': 'motorola', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  int SteerAngleRearActual();

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'Steer_AngleSpeedActual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|250]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
  int SteerAngleSpeedActual();

  // config detail: {'bit': 23, 'description': 'Steer system communication fault', 'enum': {0: 'STEER_FLT2_NO_FAULT', 1: 'STEER_FLT2_STEER_SYSTEM_COMUNICATION_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Steer_Flt2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int SteerFlt2();

  // config detail: {'bit': 15, 'description': 'Steer system hardware fault', 'enum': {0: 'STEER_FLT1_NO_FAULT', 1: 'STEER_FLT1_STEER_SYSTEM_HARDWARE_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Steer_Flt1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int SteerFlt1();

  // config detail: {'bit': 1, 'enum': {0: 'STEER_ENSTATE_MANUAL', 1: 'STEER_ENSTATE_AUTO', 2: 'STEER_ENSTATE_TAKEOVER', 3: 'STEER_ENSTATE_STANDBY'}, 'is_signed_var': False, 'len': 2, 'name': 'Steer_EnState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int SteerEnState();

  // config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Steer_AngleActual', 'offset': -500.0, 'order': 'motorola', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  int SteerAngleActual();
};



