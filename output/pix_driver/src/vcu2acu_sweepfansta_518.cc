/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu2acu_sweepfansta_518.hpp"


Vcu2acusweepfansta518::Vcu2acusweepfansta518() {}
int32_t Vcu2acusweepfansta518::ID = 0x518;

void Vcu2acusweepfansta518::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcu2acusweepfansta518::Parse() {
  scu_fanconntorllermainvoltage = SCUFanConntorllerMainVoltage();
  scu_fanconntorllercurrent = SCUFanConntorllerCurrent();
  scu_fanmotortemp = SCUFanMotorTemp();
  scu_fanconntorllertemp = SCUFanConntorllerTemp();
  scu_fanconntorllererr1 = SCUFanConntorllerErr1();
  scu_fanconntorllererr2 = SCUFanConntorllerErr2();
}


// config detail: {'bit': 7, 'is_signed_var': False, 'len': 16, 'name': 'SCU_FanConntorllerMainVoltage', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|500]', 'physical_unit': 'V', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepfansta518::SCUFanConntorllerMainVoltage() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'SCU_FanConntorllerCurrent', 'offset': -2000.0, 'order': 'motorola', 'physical_range': '[-2000|2000]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepfansta518::SCUFanConntorllerCurrent() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 3));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x + -2000.000000;
  return ret;
}

// config detail: {'bit': 39, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanMotorTemp', 'offset': -40.0, 'order': 'motorola', 'physical_range': '[-40|210]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepfansta518::SCUFanMotorTemp() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanConntorllerTemp', 'offset': -40.0, 'order': 'motorola', 'physical_range': '[-40|160]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepfansta518::SCUFanConntorllerTemp() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanConntorllerErr1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepfansta518::SCUFanConntorllerErr1() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'SCU_FanConntorllerErr2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepfansta518::SCUFanConntorllerErr2() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

