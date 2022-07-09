/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Wheelspeedreport506 {
public:
    static  int32_t ID;
    Wheelspeedreport506();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double wheelspeedrr;
    double wheelspeedrl;
    double wheelspeedfr;
    double wheelspeedfl;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 55, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedRR', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
  double WheelSpeedRR();

  // config detail: {'bit': 39, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedRL', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
  double WheelSpeedRL();

  // config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedFR', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
  double WheelSpeedFR();

  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedFL', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
  double WheelSpeedFL();
};



