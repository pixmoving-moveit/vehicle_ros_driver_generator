/******************************************************************************
folongma
 *****************************************************************************/

#pragma once
#include "Byte.hpp"

class Steeringcommand102 {
public:
	static  int32_t ID;

	Steeringcommand102();

  	void UpdateData(int steer_enctrl_, int steer_angletarget_, int steer_anglespeed_, int checksum_102_);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'enum': {0: 'STEER_ENCTRL_DISABLE', 1: 'STEER_ENCTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'Steer_EnCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_steer_enctrl(int steer_enctrl);

  // config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Steer_AngleTarget', 'offset': -500.0, 'order': 'motorola', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  void set_p_steer_angletarget(int steer_angletarget);

  // config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'Steer_AngleSpeed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|250]', 'physical_unit': 'deg/s', 'precision': 1.0, 'type': 'int'}
  void set_p_steer_anglespeed(int steer_anglespeed);

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_102', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_checksum_102(int checksum_102);

private:
	uint8_t data[8];
};



