#ifndef DATA_MONITOR_HPP
#define DATA_MONITOR_HPP

#include <functional>

template <class WidthT>
struct DataMonitor
{
    std::function<WidthT(void)> monitor;
};


#endif // DATA_MONITOR_HPP