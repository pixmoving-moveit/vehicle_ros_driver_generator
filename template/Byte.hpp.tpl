#pragma once
#include <iostream>

class Byte
{
private:
    uint8_t byte_t;

public:
    Byte(std::uint8_t byte);
    ~Byte();

    uint8_t return_byte_t();
    int32_t get_byte(uint start, uint end);
    void set_value(uint8_t value, uint start, uint len);
};
