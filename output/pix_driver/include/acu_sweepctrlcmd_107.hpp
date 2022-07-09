/******************************************************************************
folongma
 *****************************************************************************/

#pragma once
#include "Byte.hpp"

class Acusweepctrlcmd107 {
public:
	static  int32_t ID;

	Acusweepctrlcmd107();

  	void UpdateData(int fanspeedctrl_, int shakerdusterctrl_, int dedustingctrl_, int autocleaningstartctrl_, int autogarbagedumpstartctrl_, int mouthpieceupdownctrl_, int sweepplateupdown_, int fanmodectrl_, int fanspeedmode_, int sweepmodectrl_, int mowingspeedctrl_);

  	void Reset();
  
  	uint8_t *get_data();


private:
	
  // config detail: {'bit': 55, 'description': '风机速度控制', 'is_signed_var': False, 'len': 16, 'name': 'FanSpeedCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
  void set_p_fanspeedctrl(int fanspeedctrl);

  // config detail: {'bit': 9, 'enum': {0: 'SHAKERDUSTERCTRL_OFF', 1: 'SHAKERDUSTERCTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'ShakerDusterCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_shakerdusterctrl(int shakerdusterctrl);

  // config detail: {'bit': 8, 'description': '喷雾降尘', 'enum': {0: 'DEDUSTINGCTRL_OFF', 1: 'DEDUSTINGCTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'DedustingCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_dedustingctrl(int dedustingctrl);

  // config detail: {'bit': 1, 'description': '一键清扫控制', 'enum': {0: 'AUTOCLEANINGSTARTCTRL_NO', 1: 'AUTOCLEANINGSTARTCTRL_START', 2: 'AUTOCLEANINGSTARTCTRL_STOP', 3: 'AUTOCLEANINGSTARTCTRL_NO'}, 'is_signed_var': False, 'len': 2, 'name': 'AutoCleaningStartCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_autocleaningstartctrl(int autocleaningstartctrl);

  // config detail: {'bit': 3, 'description': '一键倾倒', 'enum': {0: 'AUTOGARBAGEDUMPSTARTCTRL_NO', 1: 'AUTOGARBAGEDUMPSTARTCTRL_START', 2: 'AUTOGARBAGEDUMPSTARTCTRL_STOP', 3: 'AUTOGARBAGEDUMPSTARTCTRL_NO'}, 'is_signed_var': False, 'len': 2, 'name': 'AutoGarbageDumpStartCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_autogarbagedumpstartctrl(int autogarbagedumpstartctrl);

  // config detail: {'bit': 13, 'description': '吸盘升降控制', 'enum': {0: 'MOUTHPIECEUPDOWNCTRL_NO', 1: 'MOUTHPIECEUPDOWNCTRL_UP', 2: 'MOUTHPIECEUPDOWNCTRL_DOWN'}, 'is_signed_var': False, 'len': 2, 'name': 'MouthpieceUpDownCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_mouthpieceupdownctrl(int mouthpieceupdownctrl);

  // config detail: {'bit': 15, 'description': '扫盘升降', 'enum': {0: 'SWEEPPLATEUPDOWN_NO', 1: 'SWEEPPLATEUPDOWN_UP', 2: 'SWEEPPLATEUPDOWN_DOWN'}, 'is_signed_var': False, 'len': 2, 'name': 'SweepPlateUpDown', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_sweepplateupdown(int sweepplateupdown);

  // config detail: {'bit': 17, 'description': '风机工作模式', 'enum': {0: 'FANMODECTRL_OFF', 1: 'FANMODECTRL_LOW', 2: 'FANMODECTRL_MID', 3: 'FANMODECTRL_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'FanModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fanmodectrl(int fanmodectrl);

  // config detail: {'bit': 19, 'description': '风机速度模式', 'enum': {0: 'FANSPEEDMODE_DEFAULT', 1: 'FANSPEEDMODE_SPEED'}, 'is_signed_var': False, 'len': 1, 'name': 'FanSpeedMode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_fanspeedmode(int fanspeedmode);

  // config detail: {'bit': 21, 'description': '扫盘转速挡位控制', 'enum': {0: 'SWEEPMODECTRL_OFF', 1: 'SWEEPMODECTRL_LOW', 2: 'SWEEPMODECTRL_MID', 3: 'SWEEPMODECTRL_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'SweepModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_sweepmodectrl(int sweepmodectrl);

  // config detail: {'bit': 25, 'description': '割草转速挡位控制', 'enum': {0: 'MOWINGSPEEDCTRL_OFF', 1: 'MOWINGSPEEDCTRL_LOW', 2: 'MOWINGSPEEDCTRL_MID', 3: 'MOWINGSPEEDCTRL_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'MowingSpeedCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_mowingspeedctrl(int mowingspeedctrl);

private:
	uint8_t data[8];
};



