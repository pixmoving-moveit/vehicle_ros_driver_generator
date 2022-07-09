/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acuchassiserrcode3202 {
public:
    static  int32_t ID;
    Vcu2acuchassiserrcode3202();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int chassisrredserrorcode2;
    int chassisrfedserrorcode2;
    int chassislredserrorcode2;
    int chassislfedserrorcode2;
    int chassisrredserrorcode;
    int chassisrfedserrorcode;
    int chassislredserrorcode;
    int chassislfedserrorcode;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRrEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisRrEdsErrorCode2();

  // config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRfEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisRfEdsErrorCode2();

  // config detail: {'bit': 31, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLrEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisLrEdsErrorCode2();

  // config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLfEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisLfEdsErrorCode2();

  // config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRrEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisRrEdsErrorCode();

  // config detail: {'bit': 39, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRfEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisRfEdsErrorCode();

  // config detail: {'bit': 23, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLrEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisLrEdsErrorCode();

  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLfEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisLfEdsErrorCode();
};



