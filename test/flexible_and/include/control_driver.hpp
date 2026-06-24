#ifndef CONTROL_DRIVER_HPP
#define CONTROL_DRIVER_HPP

#include <functional>

struct ControlDriver
{
    std::function<void(bool)> invert_a;
    std::function<void(bool)> invert_b;
    std::function<void(bool)> invert_y;
};

#endif // CONTROL_DRIVER_HPP