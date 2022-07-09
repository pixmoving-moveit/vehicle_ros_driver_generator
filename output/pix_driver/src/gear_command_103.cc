/******************************************************************************
fulongma
 *****************************************************************************/
#include "gear_command_103.hpp"

int32_t Gearcommand103::ID = 0x103;

// public
Gearcommand103::Gearcommand103() { Reset(); }

void Gearcommand103::UpdateData(int gear_target_, int gear_enctrl_, int checksum_103_) {
  set_p_gear_target(gear_target_);
  set_p_gear_enctrl(gear_enctrl_);
  set_p_checksum_103(checksum_103_);
}

void Gearcommand103::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * Gearcommand103::get_data()
{
  return data;
}



// config detail: {'bit': 10, 'enum': {0: 'GEAR_TARGET_INVALID', 1: 'GEAR_TARGET_PARK', 2: 'GEAR_TARGET_REVERSE', 3: 'GEAR_TARGET_NEUTRAL', 4: 'GEAR_TARGET_DRIVE'}, 'is_signed_var': False, 'len': 3, 'name': 'Gear_Target', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Gearcommand103::set_p_gear_target(int gear_target) {
  int x = gear_target;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 3);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 0, 'enum': {0: 'GEAR_ENCTRL_DISABLE', 1: 'GEAR_ENCTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'Gear_EnCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Gearcommand103::set_p_gear_enctrl(int gear_enctrl) {
  int x = gear_enctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_103', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Gearcommand103::set_p_checksum_103(int checksum_103) {
  // checksum_103 = ProtocolData::BoundedValue(0, 255, checksum_103);
  int x = checksum_103;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


