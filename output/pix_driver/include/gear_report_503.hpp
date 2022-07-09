/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Gearreport503 {
public:
    static  int32_t ID;
    Gearreport503();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int gear_flt;
    int gear_actual;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 15, 'enum': {0: 'GEAR_FLT_NO_FAULT', 1: 'GEAR_FLT_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Gear_Flt', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int GearFlt();

  // config detail: {'bit': 2, 'enum': {0: 'GEAR_ACTUAL_INVALID', 1: 'GEAR_ACTUAL_PARK', 2: 'GEAR_ACTUAL_REVERSE', 3: 'GEAR_ACTUAL_NEUTRAL', 4: 'GEAR_ACTUAL_DRIVE'}, 'is_signed_var': False, 'len': 3, 'name': 'Gear_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int GearActual();
};



