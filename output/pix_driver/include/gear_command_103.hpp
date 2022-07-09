/******************************************************************************
folongma
 *****************************************************************************/

#pragma once
#include "Byte.hpp"

class Gearcommand103 {
public:
	static  int32_t ID;

	Gearcommand103();

  	void UpdateData(int gear_target_, int gear_enctrl_, int checksum_103_);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 10, 'enum': {0: 'GEAR_TARGET_INVALID', 1: 'GEAR_TARGET_PARK', 2: 'GEAR_TARGET_REVERSE', 3: 'GEAR_TARGET_NEUTRAL', 4: 'GEAR_TARGET_DRIVE'}, 'is_signed_var': False, 'len': 3, 'name': 'Gear_Target', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_gear_target(int gear_target);

  // config detail: {'bit': 0, 'enum': {0: 'GEAR_ENCTRL_DISABLE', 1: 'GEAR_ENCTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'Gear_EnCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_gear_enctrl(int gear_enctrl);

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_103', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_checksum_103(int checksum_103);

private:
	uint8_t data[8];
};



