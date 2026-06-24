#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <cstdint>
#include <memory>
#include <queue>
#include <string>

#include "clock_driver.hpp"
#include "control_driver.hpp"
#include "data_driver.hpp"
#include "data_monitor.hpp"
#include "model.hpp"

class VerilatedContext;
class VerilatedVcdC;
class Vflexible_and;

class Environment
{
private:
    using WidthT = std::uint8_t;

public:
    Environment(const std::string& testCaseName, int traceLevel = 0);
    ~Environment();
    void EnqueueTransaction(WidthT aInput, WidthT bInput);
    void ResetDut(std::size_t reset_cycles = 1);
    void Run();
    const ControlDriver& GetControl();

private:
    struct Transaction
    {
        WidthT a;
        WidthT b;
    };

    void WaitCycles(std::size_t cycles = 1);
    static std::unique_ptr<VerilatedContext> MakeContext();

    std::string                       m_vcdFileName;
    std::unique_ptr<VerilatedContext> m_ctx;
    std::unique_ptr<VerilatedVcdC>    m_trace;
    std::unique_ptr<Vflexible_and>    m_dut;
    std::uint64_t                     m_timeCounter;
    Model<WidthT>                     m_dutModel;
    ClockDriver                       m_clockDriver;
    ControlDriver                     m_ctrlDriver;
    DataDriver<WidthT>                m_dataDriver;
    DataMonitor<WidthT>               m_dataMonitor;
    std::queue<Transaction>           m_transactions;
};

#endif // ENVIRONMENT_HPP