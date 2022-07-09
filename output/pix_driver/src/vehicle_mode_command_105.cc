/******************************************************************************
fulongma
 *****************************************************************************/
#include "vehicle_mode_command_105.hpp"

int32_t Vehiclemodecommand105::ID = 0x105;

// public
Vehiclemodecommand105::Vehiclemodecommand105() { Reset(); }

void Vehiclemodecommand105::UpdateData(int headlight_ctrl_, int checksum_105_, int turnlight_ctrl_, int drive_modectrl_, int steer_modectrl_) {
  set_p_headlight_ctrl(headlight_ctrl_);
  set_p_checksum_105(checksum_105_);
  set_p_turnlight_ctrl(turnlight_ctrl_);
  set_p_drive_modectrl(drive_modectrl_);
  set_p_steer_modectrl(steer_modectrl_);
}

void Vehiclemodecommand105::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * Vehiclemodecommand105::get_data()
{
  return data;
}



// config detail: {'bit': 18, 'enum': {0: 'HEADLIGHT_CTRL_OFF', 1: 'HEADLIGHT_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'Headlight_Ctrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vehiclemodecommand105::set_p_headlight_ctrl(int headlight_ctrl) {
  int x = headlight_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 1);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_105', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void Vehiclemodecommand105::set_p_checksum_105(int checksum_105) {
  // checksum_105 = ProtocolData::BoundedValue(0, 255, checksum_105);
  int x = checksum_105;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}

// config detail: {'bit': 17, 'enum': {0: 'TURNLIGHT_CTRL_TURNLAMP_OFF', 1: 'TURNLIGHT_CTRL_LEFT_TURNLAMP_ON', 2: 'TURNLIGHT_CTRL_RIGHT_TURNLAMP_ON', 3: 'TURNLIGHT_CTRL_HAZARD_WARNING_LAMPSTS_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'TurnLight_Ctrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vehiclemodecommand105::set_p_turnlight_ctrl(int turnlight_ctrl) {
  int x = turnlight_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 2);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 10, 'enum': {0: 'DRIVE_MODECTRL_THROTTLE_PADDLE_DRIVE', 1: 'DRIVE_MODECTRL_SPEED_DRIVE'}, 'is_signed_var': False, 'len': 3, 'name': 'Drive_ModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vehiclemodecommand105::set_p_drive_modectrl(int drive_modectrl) {
  int x = drive_modectrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 3);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 2, 'enum': {0: 'STEER_MODECTRL_STANDARD_STEER', 1: 'STEER_MODECTRL_NON_DIRECTION_STEER', 2: 'STEER_MODECTRL_SYNC_DIRECTION_STEER'}, 'is_signed_var': False, 'len': 3, 'name': 'Steer_ModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Vehiclemodecommand105::set_p_steer_modectrl(int steer_modectrl) {
  int x = steer_modectrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 3);
  data[0] += to_set.return_byte_t();
  
}


