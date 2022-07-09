/******************************************************************************
folongma
 *****************************************************************************/

#pragma once
#include "Byte.hpp"

class Throttlecommand100 {
public:
	static  int32_t ID;

	Throttlecommand100();

  	void UpdateData(double dirve_speedtarget_, int checksum_100_, double dirve_throttlepedaltarget_, int dirve_enctrl_);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 47, 'is_signed_var': False, 'len': 12, 'name': 'Dirve_SpeedTarget', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|40.95]', 'physical_unit': 'm/s', 'precision': 0.01, 'type': 'double'}
  void set_p_dirve_speedtarget(double dirve_speedtarget);

  // config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'CheckSum_100', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_checksum_100(int checksum_100);

  // config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Dirve_ThrottlePedalTarget', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
  void set_p_dirve_throttlepedaltarget(double dirve_throttlepedaltarget);

  // config detail: {'bit': 0, 'enum': {0: 'DIRVE_ENCTRL_DISABLE', 1: 'DIRVE_ENCTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'Dirve_EnCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_dirve_enctrl(int dirve_enctrl);

private:
	uint8_t data[8];
};



