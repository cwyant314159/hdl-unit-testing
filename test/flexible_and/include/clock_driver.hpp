#ifndef CLOCK_DRIVER_HPP
#define CLOCK_DRIVER_HPP

#include <functional>

struct ClockDriver
{
    std::function<void(void)> tick;
    std::function<void(bool)> reset;
};

#endif // CLOCK_DRIVER