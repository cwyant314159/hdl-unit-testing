cmake_minimum_required(VERSION 3.15)

#
# Control Device test application
#
add_executable(
    test_control_device
    control_device/sim_dut.hpp
    control_device/sim_dut.cpp
    control_device/test.cpp
    test_main.cpp
)