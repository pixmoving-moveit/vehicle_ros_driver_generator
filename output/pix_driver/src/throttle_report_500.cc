/******************************************************************************
 fulongma
 *****************************************************************************/
#include "throttle_report_500.hpp"


Throttlereport500::Throttlereport500() {}
int32_t Throttlereport500::ID = 0x500;

void Throttlereport500::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Throttlereport500::Parse() {
  dirve_throttlepedalactual = DirveThrottlePedalActual();
  dirve_flt2 = DirveFlt2();
  dirve_flt1 = DirveFlt1();
  dirve_enstate = DirveEnState();
}


// config detail: {'bit': 31, 'is_signed_var': False, 'len': 16, 'name': 'Dirve_ThrottlePedalActual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
double Throttlereport500::DirveThrottlePedalActual() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 23, 'description': 'Drive system communication fault', 'enum': {0: 'DIRVE_FLT2_NO_FAULT', 1: 'DIRVE_FLT2_DRIVE_SYSTEM_COMUNICATION_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Dirve_Flt2', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Throttlereport500::DirveFlt2() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 15, 'description': 'Drive system hardware fault', 'enum': {0: 'DIRVE_FLT1_NO_FAULT', 1: 'DIRVE_FLT1_DRIVE_SYSTEM_HARDWARE_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Dirve_Flt1', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Throttlereport500::DirveFlt1() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'enum': {0: 'DIRVE_ENSTATE_MANUAL', 1: 'DIRVE_ENSTATE_AUTO', 2: 'DIRVE_ENSTATE_TAKEOVER', 3: 'DIRVE_ENSTATE_STANDBY'}, 'is_signed_var': False, 'len': 2, 'name': 'Dirve_EnState', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Throttlereport500::DirveEnState() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

