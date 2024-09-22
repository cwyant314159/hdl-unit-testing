cmake_minimum_required(VERSION 3.15)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
Set(FETCHCONTENT_QUIET FALSE)

project(
    HdlUnitTesting
    VERSION
        1.0
    DESCRIPTION
        "Simple HDL design with Googletest/Verilator verification"
    LANGUAGES
        CXX
        C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-O2 -flto=auto")
set(CMAKE_EXE_LINKER_FLAG "-flto=auto")

#
# Fetch the googletest library, and it to the build.
#
FetchContent_Declare(
    googletest
    GIT_REPOSITORY
        https://github.com/google/googletest.git
    GIT_TAG
        v1.15.2
    GIT_PROGRESS
        TRUE
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest)

add_subdirectory(hdl)
add_subdirectory(test)

#
# Link all the applications and libraries together
#
target_link_libraries(test_flexible_and verilated_flexible_and GTest::GTest)
