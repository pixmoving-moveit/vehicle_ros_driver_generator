/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acuchassiserrcode2201 {
public:
    static  int32_t ID;
    Vcu2acuchassiserrcode2201();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int chassisebserrorcode3;
    int chassisbmserrorcode;
    int chassisbackepserrorcode;
    int chassisfrontepserrorcode;
    int chassisebserrorcode2;
    int chassisebserrorcode1;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'ChassisEbsErrorCode3', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisEbsErrorCode3();

  // config detail: {'bit': 23, 'is_signed_var': False, 'len': 8, 'name': 'ChassisBmsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisBmsErrorCode();

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'ChassisBackEpsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisBackEpsErrorCode();

  // config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'ChassisFrontEpsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisFrontEpsErrorCode();

  // config detail: {'bit': 39, 'is_signed_var': False, 'len': 8, 'name': 'ChassisEbsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisEbsErrorCode2();

  // config detail: {'bit': 31, 'is_signed_var': False, 'len': 8, 'name': 'ChassisEbsErrorCode1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int ChassisEbsErrorCode1();
};



