#include "Byte.hpp" 

Byte::Byte(std::uint8_t bytes)
{
    byte_t = bytes;
}

Byte::~Byte()
{
}

int32_t Byte::get_byte(uint start, uint len)
{
    uint8_t new_byte;
    new_byte = byte_t << (8-start-len);
    new_byte = new_byte >> (8-len);
    return static_cast<int32_t>(new_byte);
}

uint8_t Byte::return_byte_t()
{
    return byte_t;
}

void Byte::set_value(uint8_t value, uint start, uint len)
{
    value <<= (8-len);
    value >>= (8-start-len);
    byte_t += value;
}
