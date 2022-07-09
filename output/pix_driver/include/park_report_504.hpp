/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Parkreport504 {
public:
    static  int32_t ID;
    Parkreport504();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int parking_actual;
    int park_flt;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 0, 'enum': {0: 'PARKING_ACTUAL_RELEASE', 1: 'PARKING_ACTUAL_PARKING_TRIGGER'}, 'is_signed_var': False, 'len': 1, 'name': 'Parking_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int ParkingActual();

  // config detail: {'bit': 15, 'enum': {0: 'PARK_FLT_NO_FAULT', 1: 'PARK_FLT_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Park_Flt', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int ParkFlt();
};



