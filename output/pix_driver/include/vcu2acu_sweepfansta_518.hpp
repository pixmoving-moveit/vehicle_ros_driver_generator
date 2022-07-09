/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acusweepfansta518 {
public:
    static  int32_t ID;
    Vcu2acusweepfansta518();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int scu_fanconntorllermainvoltage;
    int scu_fanconntorllercurrent;
    int scu_fanmotortemp;
    int scu_fanconntorllertemp;
    int scu_fanconntorllererr1;
    int scu_fanconntorllererr2;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 16, 'name': 'SCU_FanConntorllerMainVoltage', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
  int SCUFanConntorllerMainVoltage();

  // config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'SCU_FanConntorllerCurrent', 'offset': -2000.0, 'order': 'motorola', 'physical_range': '[-2000|2000]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
  int SCUFanConntorllerCurrent();

  // config detail: {'bit': 39, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanMotorTemp', 'offset': -40.0, 'order': 'motorola', 'physical_range': '[-40|210]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int SCUFanMotorTemp();

  // config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanConntorllerTemp', 'offset': -40.0, 'order': 'motorola', 'physical_range': '[-40|160]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int SCUFanConntorllerTemp();

  // config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanConntorllerErr1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUFanConntorllerErr1();

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanConntorllerErr2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUFanConntorllerErr2();
};



