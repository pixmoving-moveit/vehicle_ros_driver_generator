/******************************************************************************
 fulongma
 *****************************************************************************/

#pragma once

#include "Byte.hpp"
#include <iostream>

class %(classname)s {
public:
    static  int32_t ID;
    %(classname)s();
    void Parse();
    void update_bytes(uint8_t bytes_data[8]);
    // singal
    %(signalname_variable)s

private:
    uint8_t bytes[8];
    %(func_declare_list)s
};



