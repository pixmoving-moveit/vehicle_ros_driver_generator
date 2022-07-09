/******************************************************************************
folongma
 *****************************************************************************/

#pragma once
#include "Byte.hpp"

class Brakecommand101 {
public:
	static  int32_t ID;

	Brakecommand101();

  	void UpdateData(int checksum_101_, double brake_pedal_target_, int brake_enctrl_);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_101', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_checksum_101(int checksum_101);

  // config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Brake_Pedal_Target', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
  void set_p_brake_pedal_target(double brake_pedal_target);

  // config detail: {'bit': 0, 'enum': {0: 'BRAKE_ENCTRL_DISABLE', 1: 'BRAKE_ENCTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'Brake_EnCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_brake_enctrl(int brake_enctrl);

private:
	uint8_t data[8];
};



