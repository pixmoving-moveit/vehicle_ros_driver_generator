/******************************************************************************
 fulongma
 *****************************************************************************/
#include "wheelspeed_report_506.hpp"


Wheelspeedreport506::Wheelspeedreport506() {}
int32_t Wheelspeedreport506::ID = 0x506;

void Wheelspeedreport506::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Wheelspeedreport506::Parse() {
  wheelspeedrr = WheelSpeedRR();
  wheelspeedrl = WheelSpeedRL();
  wheelspeedfr = WheelSpeedFR();
  wheelspeedfl = WheelSpeedFL();
}


// config detail: {'bit': 55, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedRR', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
double Wheelspeedreport506::WheelSpeedRR() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 7));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.001000;
  return ret;
}

// config detail: {'bit': 39, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedRL', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
double Wheelspeedreport506::WheelSpeedRL() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 5));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.001000;
  return ret;
}

// config detail: {'bit': 23, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedFR', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
double Wheelspeedreport506::WheelSpeedFR() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 3));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.001000;
  return ret;
}

// config detail: {'bit': 7, 'is_signed_var': False, 'len': 16, 'name': 'WheelSpeedFL', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|65.535]', 'physical_unit': 'm/s', 'precision': 0.001, 'type': 'double'}
double Wheelspeedreport506::WheelSpeedFL() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.001000;
  return ret;
}

