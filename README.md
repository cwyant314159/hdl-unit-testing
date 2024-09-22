# HDL Unit Testing

A simple project demonstrating an HDL verification workflow using Verilator
and GoogleTest.

## Building

The bash script `project_build.sh` is provided to do the CMake and Make calls
to build the unit test binary __test_flexible_and__. The build assumes that
Verilator is installed on the system path. The GoogleTest dependency is handled
by CMake.

## Running

To run the unit tests, execute the following in the repository root:

```bash
./project_build.sh && ./build/test/test_flexible_and
```

## Wave Files

Each test case generates a separate wave file in the working directory of the
test binary. Waveform files have the naming scheme `<fixture>_<test case>.vcd`.
The _fixture_ and _test case_ strings come from the GoogleTest macros:

```cpp
TEST_F(Fixture, TestCase)
{
    // ... test code ...
}
```

## Test Binary Command Line Arguments

Test binaries are written such that command line arguments can be passed to
both the GoogleTest and Verilator runtimes. Verilator arguments are parsed
before the GoogleTest arguments. If the given Verilator argument causes the
application to exit, GoogleTest will not have a chance to parse its arguments.

The example below shows a GoogleTest filter for all test cases that start with
the string "Regular" and sets the Verilator random seed.

```bash
./build/test/test_flexible_and --gtest_filter=*.Regular* +verilator+seed+69
```
