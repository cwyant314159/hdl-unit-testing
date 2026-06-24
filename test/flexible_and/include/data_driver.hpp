#ifndef DATA_DRIVER_HPP
#define DATA_DRIVER_HPP

#include <functional>

template <class WidthT>
struct DataDriver
{
    std::function<void(WidthT, WidthT)> drive;
};

#endif // DATA_DRIVER_HPP