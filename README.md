# HDL Unit Testing

A simple project demonstrating an HDL verification workflow using Verilator
and GoogleTest.

## Building and Running

CMake presets can be used to build and test this project in either `debug` or
`release` mode. The build assumes that Verilator is installed on the system.
The GoogleTest dependency is cloned using `FetchContent` during CMake's
configure step.

```bash
# debug
cmake --preset debug
cmake --build --preset debug
ctest --preset debug

# release
cmake --preset release
cmake --build --preset release
ctest --preset release
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

> __NOTE__: `ctest` executes the unit test executables in their respective
> build folder.

## Test Binary Command Line Arguments

Test binaries are written such that command line arguments can be passed to
both the GoogleTest and Verilator runtimes. GoogleTest arguments are parsed
before the Verilator arguments. If the given GoogleTest argument causes the
application to exit, Verilator will not have a chance to parse its arguments.

The example below shows a GoogleTest filter for all test cases that start with
the string "Regular" and sets the Verilator random seed.

```bash
./build/test/test_flexible_and --gtest_filter=*.Regular* +verilator+seed+69
```
