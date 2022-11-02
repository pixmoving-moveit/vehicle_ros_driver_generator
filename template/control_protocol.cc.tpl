#include "%(protocol_name_lower)s.hpp"

int32_t %(classname)s::ID = 0x%(id_upper)s;

// public
%(classname)s::%(classname)s() { Reset(); }

void %(classname)s::UpdateData(%(signalname_list)s) {
%(set_private_var_list)s
}

void %(classname)s::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * %(classname)s::get_data()
{
  return data;
}



%(set_func_impl_list)s

