#include <pix_%(car_type_lower)s_driver/%(protocol_name_lower)s.hpp>


%(classname)s::%(classname)s() {}

void %(classname)s::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void %(classname)s::Parse() {
%(set_var_to_protocol_list)s
}

%(func_impl_list)s

