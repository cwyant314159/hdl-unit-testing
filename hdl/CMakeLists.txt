#
# Look for the verilator executable
#
find_package(verilator CONFIG REQUIRED)

#
# Verilation targets
#
add_library(verilated_flexible_and)
verilate(
    verilated_flexible_and
    SOURCES
        flexible_and.sv
    TRACE_VCD
    VERILATOR_ARGS
        --x-assign unique
        --x-initial unique
        -Wall
        -Wpedantic
        -Wwarn-lint
        -Wwarn-style
)