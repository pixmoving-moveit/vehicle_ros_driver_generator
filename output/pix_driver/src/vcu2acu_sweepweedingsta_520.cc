/******************************************************************************
 fulongma
 *****************************************************************************/
#include "vcu2acu_sweepweedingsta_520.hpp"


Vcu2acusweepweedingsta520::Vcu2acusweepweedingsta520() {}
int32_t Vcu2acusweepweedingsta520::ID = 0x520;

void Vcu2acusweepweedingsta520::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void Vcu2acusweepweedingsta520::Parse() {
  scu_weedingsta = SCUWeedingSta();
}


// config detail: {'bit': 7, 'is_signed_var': False, 'len': 8, 'name': 'SCU_WeedingSta', 'offset': 0.0, 'order': 'motorola', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int Vcu2acusweepweedingsta520::SCUWeedingSta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

