#ifndef SIM_DUT_HPP
#define SIM_DUT_HPP

#include <memory>
#include <queue>

#include <verilated_vcd_c.h>

#include "Vflexible_and.h"
#include "transaction.hpp"

class SimDut
{
public:

    SimDut(std::string suite_name, std::string test_name);
    ~SimDut();

    void reset(std::size_t num_cycles = 1);
    void enqueueTransaction(Transaction t);
    void evaluate();

private:
    void wait_cycles(std::size_t cycles);

    std::unique_ptr<VerilatedContext> ctx;
    std::unique_ptr<Vflexible_and> dut;
    std::unique_ptr<VerilatedVcdC> trace;
    size_t time;
    std::queue<Transaction> transactions;
    std::queue<std::uint8_t> expected_y;
};

#endif // SIM_DUT_HPP