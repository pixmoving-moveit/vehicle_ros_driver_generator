/******************************************************************************
fulongma
 *****************************************************************************/
#include "acu_sweepctrlcmd_107.hpp"

int32_t Acusweepctrlcmd107::ID = 0x107;

// public
Acusweepctrlcmd107::Acusweepctrlcmd107() { Reset(); }

void Acusweepctrlcmd107::UpdateData(int fanspeedctrl_, int shakerdusterctrl_, int dedustingctrl_, int autocleaningstartctrl_, int autogarbagedumpstartctrl_, int mouthpieceupdownctrl_, int sweepplateupdown_, int fanmodectrl_, int fanspeedmode_, int sweepmodectrl_, int mowingspeedctrl_) {
  set_p_fanspeedctrl(fanspeedctrl_);
  set_p_shakerdusterctrl(shakerdusterctrl_);
  set_p_dedustingctrl(dedustingctrl_);
  set_p_autocleaningstartctrl(autocleaningstartctrl_);
  set_p_autogarbagedumpstartctrl(autogarbagedumpstartctrl_);
  set_p_mouthpieceupdownctrl(mouthpieceupdownctrl_);
  set_p_sweepplateupdown(sweepplateupdown_);
  set_p_fanmodectrl(fanmodectrl_);
  set_p_fanspeedmode(fanspeedmode_);
  set_p_sweepmodectrl(sweepmodectrl_);
  set_p_mowingspeedctrl(mowingspeedctrl_);
}

void Acusweepctrlcmd107::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * Acusweepctrlcmd107::get_data()
{
  return data;
}



// config detail: {'bit': 55, 'description': '风机速度控制', 'is_signed_var': False, 'len': 16, 'name': 'FanSpeedCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
void Acusweepctrlcmd107::set_p_fanspeedctrl(int fanspeedctrl) {
  // fanspeedctrl = ProtocolData::BoundedValue(0, 0, fanspeedctrl);
  int x = fanspeedctrl;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[7] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[6] += to_set1.return_byte_t();
}

// config detail: {'bit': 9, 'enum': {0: 'SHAKERDUSTERCTRL_OFF', 1: 'SHAKERDUSTERCTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'ShakerDusterCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_shakerdusterctrl(int shakerdusterctrl) {
  int x = shakerdusterctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 1, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '喷雾降尘', 'enum': {0: 'DEDUSTINGCTRL_OFF', 1: 'DEDUSTINGCTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'DedustingCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_dedustingctrl(int dedustingctrl) {
  int x = dedustingctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 1, 'description': '一键清扫控制', 'enum': {0: 'AUTOCLEANINGSTARTCTRL_NO', 1: 'AUTOCLEANINGSTARTCTRL_START', 2: 'AUTOCLEANINGSTARTCTRL_STOP', 3: 'AUTOCLEANINGSTARTCTRL_NO'}, 'is_signed_var': False, 'len': 2, 'name': 'AutoCleaningStartCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_autocleaningstartctrl(int autocleaningstartctrl) {
  int x = autocleaningstartctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 2);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 3, 'description': '一键倾倒', 'enum': {0: 'AUTOGARBAGEDUMPSTARTCTRL_NO', 1: 'AUTOGARBAGEDUMPSTARTCTRL_START', 2: 'AUTOGARBAGEDUMPSTARTCTRL_STOP', 3: 'AUTOGARBAGEDUMPSTARTCTRL_NO'}, 'is_signed_var': False, 'len': 2, 'name': 'AutoGarbageDumpStartCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_autogarbagedumpstartctrl(int autogarbagedumpstartctrl) {
  int x = autogarbagedumpstartctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 2);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 13, 'description': '吸盘升降控制', 'enum': {0: 'MOUTHPIECEUPDOWNCTRL_NO', 1: 'MOUTHPIECEUPDOWNCTRL_UP', 2: 'MOUTHPIECEUPDOWNCTRL_DOWN'}, 'is_signed_var': False, 'len': 2, 'name': 'MouthpieceUpDownCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_mouthpieceupdownctrl(int mouthpieceupdownctrl) {
  int x = mouthpieceupdownctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 2);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 15, 'description': '扫盘升降', 'enum': {0: 'SWEEPPLATEUPDOWN_NO', 1: 'SWEEPPLATEUPDOWN_UP', 2: 'SWEEPPLATEUPDOWN_DOWN'}, 'is_signed_var': False, 'len': 2, 'name': 'SweepPlateUpDown', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_sweepplateupdown(int sweepplateupdown) {
  int x = sweepplateupdown;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 6, 2);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 17, 'description': '风机工作模式', 'enum': {0: 'FANMODECTRL_OFF', 1: 'FANMODECTRL_LOW', 2: 'FANMODECTRL_MID', 3: 'FANMODECTRL_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'FanModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_fanmodectrl(int fanmodectrl) {
  int x = fanmodectrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 2);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 19, 'description': '风机速度模式', 'enum': {0: 'FANSPEEDMODE_DEFAULT', 1: 'FANSPEEDMODE_SPEED'}, 'is_signed_var': False, 'len': 1, 'name': 'FanSpeedMode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_fanspeedmode(int fanspeedmode) {
  int x = fanspeedmode;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 3, 1);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 21, 'description': '扫盘转速挡位控制', 'enum': {0: 'SWEEPMODECTRL_OFF', 1: 'SWEEPMODECTRL_LOW', 2: 'SWEEPMODECTRL_MID', 3: 'SWEEPMODECTRL_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'SweepModeCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_sweepmodectrl(int sweepmodectrl) {
  int x = sweepmodectrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 2);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 25, 'description': '割草转速挡位控制', 'enum': {0: 'MOWINGSPEEDCTRL_OFF', 1: 'MOWINGSPEEDCTRL_LOW', 2: 'MOWINGSPEEDCTRL_MID', 3: 'MOWINGSPEEDCTRL_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'MowingSpeedCtrl', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void Acusweepctrlcmd107::set_p_mowingspeedctrl(int mowingspeedctrl) {
  int x = mowingspeedctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 2);
  data[3] += to_set.return_byte_t();
  
}


