#include "environment.hpp"

#include <gtest/gtest.h>
#include <verilated_vcd_c.h>

#include "program_args.hpp"
#include "Vflexible_and.h"

Environment::Environment(const std::string& testCaseName, int traceLevel)
    : m_vcdFileName{testCaseName + ".vcd"}
    , m_ctx{MakeContext()}
    , m_trace{std::make_unique<VerilatedVcdC>()}
    , m_dut{std::make_unique<Vflexible_and>(m_ctx.get())}
    , m_timeCounter{0}
    , m_clockDriver{}
    , m_ctrlDriver{}
    , m_dataDriver{}
    , m_dataMonitor{}
    , m_transactions{}
{
    // Wire the DUT to the drivers, monitors, and model
    m_clockDriver.reset = [this](bool state) -> void {m_dut->reset = state; };

    m_clockDriver.tick = [this]() -> void {
        m_dut->clock = 1;
        m_dut->eval();
        m_trace->dump(m_timeCounter++);

        m_dut->clock = 0;
        m_dut->eval();
        m_trace->dump(m_timeCounter++);
    };

    m_ctrlDriver.invert_a = [this](bool state) -> void {
        m_dut->invert_a = state;
        m_dutModel.SetInvertA(state);
    };

    m_ctrlDriver.invert_b = [this](bool state) -> void {
        m_dut->invert_b = state;
        m_dutModel.SetInvertB(state);
    };

    m_ctrlDriver.invert_y = [this](bool state) -> void {
        m_dut->invert_y = state;
        m_dutModel.SetInvertY(state);
    };


    m_dataDriver.drive = [this](WidthT a, WidthT b) -> void {
        m_dut->a = a;
        m_dut->b = b;
    };

    m_dataMonitor.monitor = [this]() -> WidthT { return m_dut->y; };

    // Setup the verilator infrastructure
    m_ctx->traceEverOn(true);
    m_dut->trace(m_trace.get(), traceLevel);
    m_trace->open(m_vcdFileName.c_str());

    // Set initial values for the clocking and reset interface
    m_dut->clock = 0;
    m_dut->reset = 0;
    m_dut->eval();
}

Environment::~Environment()
{
    WaitCycles(5);
    m_trace->close();
}

void Environment::EnqueueTransaction(WidthT aInput, WidthT bInput)
{
    m_transactions.emplace(aInput, bInput);
}

void Environment::ResetDut(std::size_t reset_cycles)
{
    m_clockDriver.reset(1);
    WaitCycles(reset_cycles);
    m_clockDriver.reset(0);
}

void Environment::Run()
{
    while (!m_transactions.empty()) {
        const Transaction& t = m_transactions.front();
        m_dataDriver.drive(t.a, t.b);

        WaitCycles(2); // let DUT pipeline process

        const WidthT expected = m_dutModel.Compute(t.a, t.b);
        EXPECT_EQ(expected, m_dataMonitor.monitor()) << "a = " << +t.a
            << "; b = " << +t.b << '\n';

        m_transactions.pop();
    }
}

const ControlDriver& Environment::GetControl()
{
    return m_ctrlDriver;
}

void Environment::WaitCycles(std::size_t cycles)
{
    for (std::size_t i = 0; i < cycles; ++i) {
        m_clockDriver.tick();
    }
}

std::unique_ptr<VerilatedContext> Environment::MakeContext()
{
    auto ctx = std::make_unique<VerilatedContext>();
    ctx->commandArgs(g_programArgs.argc, g_programArgs.argv);
    return ctx;
}