#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <cstdint>

struct Transaction
{
    std::uint8_t a = 0U;
    std::uint8_t b = 0U;
    bool invert_a  = false;
    bool invert_b  = false;
    bool invert_y  = false;
};


#endif // TRANSACTION_HPP