/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Throttlereport500 {
public:
    static  int32_t ID;
    Throttlereport500();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    double dirve_throttlepedalactual;
    int dirve_flt2;
    int dirve_flt1;
    int dirve_enstate;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Dirve_ThrottlePedalActual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
  double DirveThrottlePedalActual();

  // config detail: {'bit': 23, 'description': 'Drive system communication fault', 'enum': {0: 'DIRVE_FLT2_NO_FAULT', 1: 'DIRVE_FLT2_DRIVE_SYSTEM_COMUNICATION_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Dirve_Flt2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int DirveFlt2();

  // config detail: {'bit': 15, 'description': 'Drive system hardware fault', 'enum': {0: 'DIRVE_FLT1_NO_FAULT', 1: 'DIRVE_FLT1_DRIVE_SYSTEM_HARDWARE_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Dirve_Flt1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int DirveFlt1();

  // config detail: {'bit': 1, 'enum': {0: 'DIRVE_ENSTATE_MANUAL', 1: 'DIRVE_ENSTATE_AUTO', 2: 'DIRVE_ENSTATE_TAKEOVER', 3: 'DIRVE_ENSTATE_STANDBY'}, 'is_signed_var': False, 'len': 2, 'name': 'Dirve_EnState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int DirveEnState();
};



