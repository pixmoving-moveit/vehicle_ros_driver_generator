/******************************************************************************
 fulongma
 *****************************************************************************/
#include "gear_report_503.hpp"


Gearreport503::Gearreport503() {}
int32_t Gearreport503::ID = 0x503;

void Gearreport503::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Gearreport503::Parse() {
  gear_flt = GearFlt();
  gear_actual = GearActual();
}


// config detail: {'bit': 15, 'enum': {0: 'GEAR_FLT_NO_FAULT', 1: 'GEAR_FLT_FAULT'}, 'is_signed_var': False, 'len': 8, 'name': 'Gear_Flt', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Gearreport503::GearFlt() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'enum': {0: 'GEAR_ACTUAL_INVALID', 1: 'GEAR_ACTUAL_PARK', 2: 'GEAR_ACTUAL_REVERSE', 3: 'GEAR_ACTUAL_NEUTRAL', 4: 'GEAR_ACTUAL_DRIVE'}, 'is_signed_var': False, 'len': 3, 'name': 'Gear_Actual', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int Gearreport503::GearActual() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 3);

  int ret =  static_cast<int>(x);
  return ret;
}

