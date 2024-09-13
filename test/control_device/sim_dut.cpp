#include "sim_dut.hpp"

#include <gtest/gtest.h>

SimDut::SimDut(std::string suite_name, std::string test_name) :
    time(0),
    sequence_num(0)
{
    const std::string vcd_fname = suite_name + '_' + test_name + ".vcd";

    dut->trace(trace.get(), 99);
    trace->open(vcd_fname.c_str());

    dut->clock = 0U;
    dut->reset = 0U;
    dut->eval();
}

SimDut::~SimDut()
{
    // To make it easier to read the end of a wave file, the clock is allowed
    // to run for a few more cycles.
    wait_cycles(5);
    trace->close();
}

void SimDut::reset(std::size_t num_cycles)
{
    dut->reset = 1U;
    wait_cycles(num_cycles);
    dut->reset = 0U;
    wait_cycles(1);
}

void SimDut::enqueueOperation(Operations op, std::uint8_t a, std::uint8_t b)
{
    using namespace std;

    const uint8_t result = (Operations::OP_AND   == op) ?   a & b  :
                           (Operations::OP_OR    == op) ?   a | b  :
                           (Operations::OP_XOR   == op) ?   a ^ b  :
                           (Operations::OP_NOT_A == op) ? ~(  a  ) :
                           (Operations::OP_NAND  == op) ? ~(a & b) :
                           (Operations::OP_NOR   == op) ? ~(a | b) :
                           (Operations::OP_XNOR  == op) ? ~(a ^ b) :
                           (Operations::OP_NOT_B == op) ? ~(  b  ) :
                                                            0xFF   ;

    const uint32_t common = ((static_cast<uint32_t>(op) & CONTROL_BIT_MASK) << CONTROL_BIT_POS) |
                            ((sequence_num & SEQ_NUM_MASK  ) << SEQ_NUM_POS);

    const uint32_t task = common                                  |
                          ((a & OPERAND_A_MASK) << OPERAND_A_POS) |
                          ((b & OPERAND_B_MASK) << OPERAND_B_POS) ;

    const uint32_t resp = common                                 |
                          ((result & RESULT_MASK) << RESULT_POS) ;

    tasks.push(task);
    expected_results.push(resp);

    sequence_num += 1;
}

void SimDut::evaluate()
{
    while (!tasks.empty()) {
        // strobe in task word
        dut->task_valid = 1;
        dut->task_word  = tasks.front();
        wait_cycles(1);

        // remove task from queue
        tasks.pop();

        // monitor result interface
        dut->task_valid = 0;
        while (dut->result_valid != 1) {
            wait_cycles(1);
        }

        // verify the expected results
        EXPECT_EQ(expected_results.front(), dut->result_word);
        expected_results.pop();
    }

    EXPECT_TRUE(expected_results.empty());
}

void SimDut::wait_cycles(std::size_t cycles)
{
    for (size_t i = 0; i < cycles; i += 1) {
        // rising edge
        dut->clock = 1;
        dut->eval();
        trace->dump(time++);

        // falling edge
        dut->clock = 0;
        dut->eval();
        trace->dump(time++);
    }
}