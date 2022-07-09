/******************************************************************************
fulongma
 *****************************************************************************/
#include "brake_command_101.hpp"

int32_t Brakecommand101::ID = 0x101;

// public
Brakecommand101::Brakecommand101() { Reset(); }

void Brakecommand101::UpdateData(int checksum_101_, double brake_pedal_target_, int brake_enctrl_) {
  set_p_checksum_101(checksum_101_);
  set_p_brake_pedal_target(brake_pedal_target_);
  set_p_brake_enctrl(brake_enctrl_);
}

void Brakecommand101::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * Brakecommand101::get_data()
{
  return data;
}



// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_101', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Brakecommand101::set_p_checksum_101(int checksum_101) {
  // checksum_101 = ProtocolData::BoundedValue(0, 255, checksum_101);
  int x = checksum_101;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}

// config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Brake_Pedal_Target', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
void Brakecommand101::set_p_brake_pedal_target(double brake_pedal_target) {
  // brake_pedal_target = ProtocolData::BoundedValue(0.0, 100.0, brake_pedal_target);
  int x = brake_pedal_target / 0.100000;
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

// config detail: {'bit': 0, 'enum': {0: 'BRAKE_ENCTRL_DISABLE', 1: 'BRAKE_ENCTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'Brake_EnCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Brakecommand101::set_p_brake_enctrl(int brake_enctrl) {
  int x = brake_enctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}


