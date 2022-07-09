/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu2acu_chassiserrcode3_202.hpp"


Vcu2acuchassiserrcode3202::Vcu2acuchassiserrcode3202() {}
int32_t Vcu2acuchassiserrcode3202::ID = 0x202;

void Vcu2acuchassiserrcode3202::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcu2acuchassiserrcode3202::Parse() {
  chassisrredserrorcode2 = ChassisRrEdsErrorCode2();
  chassisrfedserrorcode2 = ChassisRfEdsErrorCode2();
  chassislredserrorcode2 = ChassisLrEdsErrorCode2();
  chassislfedserrorcode2 = ChassisLfEdsErrorCode2();
  chassisrredserrorcode = ChassisRrEdsErrorCode();
  chassisrfedserrorcode = ChassisRfEdsErrorCode();
  chassislredserrorcode = ChassisLrEdsErrorCode();
  chassislfedserrorcode = ChassisLfEdsErrorCode();
}


// config detail: {'bit': 63, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRrEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisRrEdsErrorCode2() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 47, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRfEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisRfEdsErrorCode2() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 31, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLrEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisLrEdsErrorCode2() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 15, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLfEdsErrorCode2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisLfEdsErrorCode2() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 55, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRrEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisRrEdsErrorCode() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 39, 'is_signed_var': False, 'len': 8, 'name': 'ChassisRfEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisRfEdsErrorCode() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLrEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisLrEdsErrorCode() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'ChassisLfEdsErrorCode', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|0]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acuchassiserrcode3202::ChassisLfEdsErrorCode() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

