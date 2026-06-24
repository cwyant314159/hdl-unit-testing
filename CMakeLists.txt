cmake_minimum_required(VERSION 3.27)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET FALSE)


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
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Fetch the googletest library, and it to the build.
#
FetchContent_Declare(
    googletest
    GIT_REPOSITORY
        https://github.com/google/googletest.git
    GIT_TAG
        v1.17.0
    EXCLUDE_FROM_ALL
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_subdirectory(hdl)

include(CTest)
add_subdirectory(test)
