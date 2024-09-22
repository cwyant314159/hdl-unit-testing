#include "sim_dut.hpp"

#include <gtest/gtest.h>

SimDut::SimDut(std::string suite_name, std::string test_name) :
    time(0)
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

void SimDut::enqueueTransaction(Transaction t)
{
    const std::uint8_t a_actual = (t.invert_a) ? ~t.a : t.a;
    const std::uint8_t b_actual = (t.invert_b) ? ~t.b : t.b;
    const std::uint8_t y_temp   = a_actual & b_actual;
    const std::uint8_t y_actual = (t.invert_y) ? ~y_temp : y_temp;

    transactions.push(t);
    expected_y.push(y_actual);
}

void SimDut::evaluate()
{
    while (!transactions.empty()) {
        const auto& t = transactions.front();

        // set control signals
        dut->invert_a = t.invert_a;
        dut->invert_b = t.invert_b;
        dut->invert_y = t.invert_y;

        // set the inputs
        dut->a = t.a;
        dut->b = t.b;

        // clock in the values
        wait_cycles(1);

        // remove the transaction from the queue
        transactions.pop();

        // wait a few clock cycles and check the result
        wait_cycles(1);

        EXPECT_EQ(expected_y.front(), dut->y);
        expected_y.pop();
    }

    EXPECT_TRUE(expected_y.empty());
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