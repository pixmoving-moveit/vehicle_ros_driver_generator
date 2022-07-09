/******************************************************************************
folongma
 *****************************************************************************/

#pragma once
#include "Byte.hpp"

class Vehiclemodecommand105 {
public:
	static  int32_t ID;

	Vehiclemodecommand105();

  	void UpdateData(int headlight_ctrl_, int checksum_105_, int turnlight_ctrl_, int drive_modectrl_, int steer_modectrl_);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 18, 'enum': {0: 'HEADLIGHT_CTRL_OFF', 1: 'HEADLIGHT_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'Headlight_Ctrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_headlight_ctrl(int headlight_ctrl);

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_105', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_checksum_105(int checksum_105);

  // config detail: {'bit': 17, 'enum': {0: 'TURNLIGHT_CTRL_TURNLAMP_OFF', 1: 'TURNLIGHT_CTRL_LEFT_TURNLAMP_ON', 2: 'TURNLIGHT_CTRL_RIGHT_TURNLAMP_ON', 3: 'TURNLIGHT_CTRL_HAZARD_WARNING_LAMPSTS_ON'}, 'is_signed_var': False, 'len': 2, 'name': 'TurnLight_Ctrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_turnlight_ctrl(int turnlight_ctrl);

  // config detail: {'bit': 10, 'enum': {0: 'DRIVE_MODECTRL_THROTTLE_PADDLE_DRIVE', 1: 'DRIVE_MODECTRL_SPEED_DRIVE'}, 'is_signed_var': False, 'len': 3, 'name': 'Drive_ModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_drive_modectrl(int drive_modectrl);

  // config detail: {'bit': 2, 'enum': {0: 'STEER_MODECTRL_STANDARD_STEER', 1: 'STEER_MODECTRL_NON_DIRECTION_STEER', 2: 'STEER_MODECTRL_SYNC_DIRECTION_STEER'}, 'is_signed_var': False, 'len': 3, 'name': 'Steer_ModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|7]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_steer_modectrl(int steer_modectrl);

private:
	uint8_t data[8];
};



