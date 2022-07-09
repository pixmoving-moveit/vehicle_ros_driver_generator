/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class Vcu2acusweepworksta521 {
public:
    static  int32_t ID;
    Vcu2acusweepworksta521();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    bool sweepemergencysigfb;
    int vcu_sweepplateupdownstafb;
    int vcu_autogarbagedumpstafb;
    int vcu_autocleaningstafb;
    

private:
    uint8_t bytes[8];
    
  // config detail: {'bit': 10, 'description': '清扫系统紧急停止反馈', 'is_signed_var': False, 'len': 1, 'name': 'SweepEmergencySigFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
  bool SweepEmergencySigFb();

  // config detail: {'bit': 9, 'description': '扫盘升降状态反馈', 'enum': {0: 'VCU_SWEEPPLATEUPDOWNSTAFB_NO', 1: 'VCU_SWEEPPLATEUPDOWNSTAFB_UP', 2: 'VCU_SWEEPPLATEUPDOWNSTAFB_DOWN'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_SweepPlateUpDownStaFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int VCUSweepPlateUpDownStaFb();

  // config detail: {'bit': 1, 'description': '一键倾倒状态反馈', 'enum': {0: 'VCU_AUTOGARBAGEDUMPSTAFB_OFF', 1: 'VCU_AUTOGARBAGEDUMPSTAFB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_AutoGarbageDumpStaFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int VCUAutoGarbageDumpStaFb();

  // config detail: {'bit': 0, 'description': '一键清扫状态反馈', 'enum': {0: 'VCU_AUTOCLEANINGSTAFB_OFF', 1: 'VCU_AUTOCLEANINGSTAFB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_AutoCleaningStaFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int VCUAutoCleaningStaFb();
};



