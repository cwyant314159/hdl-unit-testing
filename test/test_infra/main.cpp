#include "gtest/gtest.h"
#include "program_args.hpp"

ProgramArgs g_programArgs;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    g_programArgs.argc = argc;
    g_programArgs.argv = argv;
    return RUN_ALL_TESTS();
}