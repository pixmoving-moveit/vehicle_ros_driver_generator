/******************************************************************************
fulongma
 *****************************************************************************/
#include "throttle_command_100.hpp"

int32_t Throttlecommand100::ID = 0x100;

// public
Throttlecommand100::Throttlecommand100() { Reset(); }

void Throttlecommand100::UpdateData(double dirve_speedtarget_, int checksum_100_, double dirve_throttlepedaltarget_, int dirve_enctrl_) {
  set_p_dirve_speedtarget(dirve_speedtarget_);
  set_p_checksum_100(checksum_100_);
  set_p_dirve_throttlepedaltarget(dirve_throttlepedaltarget_);
  set_p_dirve_enctrl(dirve_enctrl_);
}

void Throttlecommand100::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * Throttlecommand100::get_data()
{
  return data;
}



// config detail: {'bit': 47, 'is_signed_var': False, 'len': 12, 'name': 'Dirve_SpeedTarget', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|40.95]', 'physical_unit': 'm/s', 'precision': 0.01, 'type': 'double'}
void Throttlecommand100::set_p_dirve_speedtarget(double dirve_speedtarget) {
  // dirve_speedtarget = ProtocolData::BoundedValue(0.0, 40.95, dirve_speedtarget);
  int x = dirve_speedtarget / 0.010000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xF;
  Byte to_set0(a);
  to_set0.set_value(t, 4, 4);
  data[6] += to_set0.return_byte_t();
  x >>= 4;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[5] += to_set1.return_byte_t();
}

// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_100', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Throttlecommand100::set_p_checksum_100(int checksum_100) {
  // checksum_100 = ProtocolData::BoundedValue(0, 255, checksum_100);
  int x = checksum_100;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}

// config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Dirve_ThrottlePedalTarget', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
void Throttlecommand100::set_p_dirve_throttlepedaltarget(double dirve_throttlepedaltarget) {
  // dirve_throttlepedaltarget = ProtocolData::BoundedValue(0.0, 100.0, dirve_throttlepedaltarget);
  int x = dirve_throttlepedaltarget / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[4] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[3] += to_set1.return_byte_t();
}

// config detail: {'bit': 0, 'enum': {0: 'DIRVE_ENCTRL_DISABLE', 1: 'DIRVE_ENCTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'Dirve_EnCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Throttlecommand100::set_p_dirve_enctrl(int dirve_enctrl) {
  int x = dirve_enctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}


