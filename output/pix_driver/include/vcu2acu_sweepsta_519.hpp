/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acusweepsta519 {
public:
    static  int32_t ID;
    Vcu2acusweepsta519();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int scu_sweeptravel_mm;
    int scu_sweepspeed;
    int scu_sweepconntrollervoltage;
    int scu_sweepconntrollercurrent;
    int scu_sweepconntorllererr1;
    int scu_sweepconntorllererr2;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepTravel_mm', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': 'mm', 'precision': 1.0, 'type': 'int'}
  int SCUSweepTravelmm();

  // config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepSpeed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
  int SCUSweepSpeed();

  // config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'SCU_SweepConntrollerVoltage', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUSweepConntrollerVoltage();

  // config detail: {'bit': 39, 'is_signed_var': False, 'len': 16, 'name': 'SCU_SweepConntrollerCurrent', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUSweepConntrollerCurrent();

  // config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepConntorllerErr1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUSweepConntorllerErr1();

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepConntorllerErr2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUSweepConntorllerErr2();
};



