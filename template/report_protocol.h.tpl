#pragma once

#include <pix_%(car_type_lower)s_driver/Byte.hpp>
#include <iostream>

class %(classname)s {
public:
    static const uint32_t ID = 0x%(id_upper)s;
    %(classname)s();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    %(signalname_variable)s

private:
    uint8_t bytes[8];
    %(func_declare_list)s
};



