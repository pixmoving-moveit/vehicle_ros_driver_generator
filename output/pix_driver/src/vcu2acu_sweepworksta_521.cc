/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu2acu_sweepworksta_521.hpp"


Vcu2acusweepworksta521::Vcu2acusweepworksta521() {}
int32_t Vcu2acusweepworksta521::ID = 0x521;

void Vcu2acusweepworksta521::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcu2acusweepworksta521::Parse() {
  sweepemergencysigfb = SweepEmergencySigFb();
  vcu_sweepplateupdownstafb = VCUSweepPlateUpDownStaFb();
  vcu_autogarbagedumpstafb = VCUAutoGarbageDumpStaFb();
  vcu_autocleaningstafb = VCUAutoCleaningStaFb();
}


// config detail: {'bit': 10, 'description': '清扫系统紧急停止反馈', 'is_signed_var': False, 'len': 1, 'name': 'SweepEmergencySigFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool Vcu2acusweepworksta521::SweepEmergencySigFb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 9, 'description': '扫盘升降状态反馈', 'enum': {0: 'VCU_SWEEPPLATEUPDOWNSTAFB_NO', 1: 'VCU_SWEEPPLATEUPDOWNSTAFB_UP', 2: 'VCU_SWEEPPLATEUPDOWNSTAFB_DOWN'}, 'is_signed_var': False, 'len': 2, 'name': 'VCU_SweepPlateUpDownStaFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcu2acusweepworksta521::VCUSweepPlateUpDownStaFb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': '一键倾倒状态反馈', 'enum': {0: 'VCU_AUTOGARBAGEDUMPSTAFB_OFF', 1: 'VCU_AUTOGARBAGEDUMPSTAFB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_AutoGarbageDumpStaFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcu2acusweepworksta521::VCUAutoGarbageDumpStaFb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 0, 'description': '一键清扫状态反馈', 'enum': {0: 'VCU_AUTOCLEANINGSTAFB_OFF', 1: 'VCU_AUTOCLEANINGSTAFB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'VCU_AutoCleaningStaFb', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Vcu2acusweepworksta521::VCUAutoCleaningStaFb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

