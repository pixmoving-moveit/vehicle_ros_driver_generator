/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu2acu_sweepsta_519.hpp"


Vcu2acusweepsta519::Vcu2acusweepsta519() {}
int32_t Vcu2acusweepsta519::ID = 0x519;

void Vcu2acusweepsta519::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcu2acusweepsta519::Parse() {
  scu_sweeptravel_mm = SCUSweepTravelmm();
  scu_sweepspeed = SCUSweepSpeed();
  scu_sweepconntrollervoltage = SCUSweepConntrollerVoltage();
  scu_sweepconntrollercurrent = SCUSweepConntrollerCurrent();
  scu_sweepconntorllererr1 = SCUSweepConntorllerErr1();
  scu_sweepconntorllererr2 = SCUSweepConntorllerErr2();
}


// config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepTravel_mm', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': 'mm', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepsta519::SCUSweepTravelmm() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepSpeed', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|255]', 'physical_unit': 'rpm', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepsta519::SCUSweepSpeed() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'SCU_SweepConntrollerVoltage', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepsta519::SCUSweepConntrollerVoltage() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 3));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 39, 'is_signed_var': False, 'len': 16, 'name': 'SCU_SweepConntrollerCurrent', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepsta519::SCUSweepConntrollerCurrent() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 5));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepConntorllerErr1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepsta519::SCUSweepConntorllerErr1() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'SCU_SweepConntorllerErr2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepsta519::SCUSweepConntorllerErr2() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

