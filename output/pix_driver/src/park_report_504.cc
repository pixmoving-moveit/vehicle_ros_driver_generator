/******************************************************************************
 fulongma
 *****************************************************************************/
#include "park_report_504.hpp"


Parkreport504::Parkreport504() {}
int32_t Parkreport504::ID = 0x504;

void Parkreport504::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Parkreport504::Parse() {
  parking_actual = ParkingActual();
  park_flt = ParkFlt();
}


// config detail: {'bit': 0, 'enum': {0: 'PARKING_ACTUAL_RELEASE', 1: 'PARKING_ACTUAL_PARKING_TRIGGER'}, 'is_signed_var': False, 'len': 1, 'name': 'Parking_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Parkreport504::ParkingActual() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 15, 'enum': {0: 'PARK_FLT_NO_FAULT', 1: 'PARK_FLT_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Park_Flt', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Parkreport504::ParkFlt() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

