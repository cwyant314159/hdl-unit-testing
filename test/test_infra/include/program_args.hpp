#ifndef ARGS_HPP
#define ARGS_HPP

struct ProgramArgs
{
    int argc;
    char** argv;
};

extern ProgramArgs g_programArgs;

#endif // ARGS_HPP