/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu2acu_chassiserrcode2_201.hpp"


Vcu2acuchassiserrcode2201::Vcu2acuchassiserrcode2201() {}
int32_t Vcu2acuchassiserrcode2201::ID = 0x201;

void Vcu2acuchassiserrcode2201::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcu2acuchassiserrcode2201::Parse() {
  chassisebserrorcode3 = ChassisEbsErrorCode3();
  chassisbmserrorcode = ChassisBmsErrorCode();
  chassisbackepserrorcode = ChassisBackEpsErrorCode();
  chassisfrontepserrorcode = ChassisFrontEpsErrorCode();
  chassisebserrorcode2 = ChassisEbsErrorCode2();
  chassisebserrorcode1 = ChassisEbsErrorCode1();
}


// config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'ChassisEbsErrorCode3', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode2201::ChassisEbsErrorCode3() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 8, 'name': 'ChassisBmsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode2201::ChassisBmsErrorCode() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'ChassisBackEpsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode2201::ChassisBackEpsErrorCode() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'ChassisFrontEpsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode2201::ChassisFrontEpsErrorCode() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 39, 'is_signed_var': False, 'len': 8, 'name': 'ChassisEbsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode2201::ChassisEbsErrorCode2() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 31, 'is_signed_var': False, 'len': 8, 'name': 'ChassisEbsErrorCode1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode2201::ChassisEbsErrorCode1() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

