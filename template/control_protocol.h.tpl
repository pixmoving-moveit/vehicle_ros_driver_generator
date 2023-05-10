#pragma once
#include <pix_%(car_type_lower)s_driver/Byte.hpp>

class %(classname)s {
public:
	static  int32_t ID;

	%(classname)s();

  	void UpdateData(%(signalname_list)s);

  	void Reset();
  
  	uint8_t *get_data();


private:
	%(declare_private_func_list)s

private:
	uint8_t data[8];
};



