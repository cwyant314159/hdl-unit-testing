cmake_minimum_required(VERSION 3.15)

#
# Flexible AND Gate test application
#
add_executable(
    test_flexible_and
    flexible_and/sim_dut.hpp
    flexible_and/sim_dut.cpp
    flexible_and/test.cpp
    test_main.cpp
)