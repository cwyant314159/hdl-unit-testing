#!/bin/bash

# This script is located at the root of the repository. Set the CMake
# source directory to the location of this script since this is the
# canonical location for the main CMakeLists.txt.
CMAKE_SRC_DIR=$(dirname $0)

# Put the CMake build directory in the repository root (CMake source
# directory).
CMAKE_BUILD_DIR="${CMAKE_SRC_DIR}/build"

# Configure the Cmake build.
cmake -S${CMAKE_SRC_DIR} -B ${CMAKE_BUILD_DIR}

# Compute the number of CPU cores to use in a parallel build.
NUM_BUILD_CORES=$((($(nproc) * 3) / 4))

# If the computed number of cores is less than or equal to 1 don't
# do a parallel build.
PARALLEL_BUILD_OPTS=
if [ "${NUM_BUILD_CORES}" -gt "1" ]; then
    PARALLEL_BUILD_OPTS="-j${NUM_BUILD_CORES}"
fi

# Do the build
cmake --build ${CMAKE_BUILD_DIR} ${PARALLEL_BUILD_OPTS}