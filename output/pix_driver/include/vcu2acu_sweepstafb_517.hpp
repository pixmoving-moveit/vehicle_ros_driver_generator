/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acusweepstafb517 {
public:
    static  int32_t ID;
    Vcu2acusweepstafb517();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    bool scu_sweeplifeend;
    bool scu_filterclogging;
    bool scu_liquidlevellow;
    bool scu_liquidlevehigh;
    int scu_liquidleve;
    bool scu_dustbinfull;
    bool scu_heartbeat;
    int scu_fanspeedfb;
    int scu_mowingspeedfb;
    int scu_sweepspeedfb;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 3, 'is_signed_var': False, 'len': 1, 'name': 'SCU_SweepLifeEnd', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool SCUSweepLifeEnd();

  // config detail: {'bit': 4, 'is_signed_var': False, 'len': 1, 'name': 'SCU_FilterClogging', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool SCUFilterClogging();

  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 1, 'name': 'SCU_LiquidLevelLow', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool SCULiquidLevelLow();

  // config detail: {'bit': 1, 'is_signed_var': False, 'len': 1, 'name': 'SCU_LiquidLeveHigh', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool SCULiquidLeveHigh();

  // config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'SCU_LiquidLeve', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCULiquidLeve();

  // config detail: {'bit': 2, 'is_signed_var': False, 'len': 1, 'name': 'SCU_DustbinFull', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool SCUDustbinFull();

  // config detail: {'bit': 7, 'is_signed_var': False, 'len': 1, 'name': 'SCU_Heartbeat', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool SCUHeartbeat();

  // config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'SCU_FanSpeedFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUFanSpeedFb();

  // config detail: {'bit': 39, 'is_signed_var': False, 'len': 16, 'name': 'SCU_MowingSpeedFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUMowingSpeedFb();

  // config detail: {'bit': 55, 'is_signed_var': False, 'len': 16, 'name': 'SCU_SweepSpeedFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int SCUSweepSpeedFb();
};



