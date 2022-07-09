/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acusweepweedingsta520 {
public:
    static  int32_t ID;
    Vcu2acusweepweedingsta520();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    int scu_weedingsta;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'SCU_WeedingSta', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUWeedingSta();
};



