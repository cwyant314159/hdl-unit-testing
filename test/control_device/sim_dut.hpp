#ifndef SIM_DUT_HPP
#define SIM_DUT_HPP

#include <cstdint>
#include <memory>
#include <queue>

#include <verilated_vcd_c.h>

#include "Vcontrol_device.h"
#include "Vcontrol_device___024root.h"

class SimDut
{
public:
    enum class Operations
    {
        OP_AND   = Vcontrol_device___024root::OP_AND,
        OP_OR    = Vcontrol_device___024root::OP_OR,
        OP_XOR   = Vcontrol_device___024root::OP_XOR,
        OP_NOT_A = Vcontrol_device___024root::OP_NOT_A,
        OP_NAND  = Vcontrol_device___024root::OP_NAND,
        OP_NOR   = Vcontrol_device___024root::OP_NOR,
        OP_XNOR  = Vcontrol_device___024root::OP_XNOR,
        OP_NOT_B = Vcontrol_device___024root::OP_NOT_B
    };

    SimDut(std::string suite_name, std::string test_name);
    ~SimDut();

    void reset(std::size_t num_cycles = 1);
    void enqueueOperation(Operations op, std::uint8_t a, std::uint8_t b);
    void evaluate();

private:
    static constexpr size_t CONTROL_BIT_POS  = 29;
    static constexpr size_t CONTROL_BIT_MASK = 0x7;

    static constexpr size_t SEQ_NUM_POS  = 16;
    static constexpr size_t SEQ_NUM_MASK = 0x1FFF;

    static constexpr size_t OPERAND_A_POS  = 8;
    static constexpr size_t OPERAND_A_MASK = 0xFF;

    static constexpr size_t OPERAND_B_POS  = 0;
    static constexpr size_t OPERAND_B_MASK = 0xFF;

    static constexpr size_t RESULT_POS  = 0;
    static constexpr size_t RESULT_MASK = 0xFF;

    void wait_cycles(std::size_t cycles);

    std::unique_ptr<Vcontrol_device> dut =
        std::unique_ptr<Vcontrol_device>(new Vcontrol_device);

    std::unique_ptr<VerilatedVcdC> trace =
        std::unique_ptr<VerilatedVcdC>(new VerilatedVcdC);

    size_t time;
    size_t sequence_num;

    std::queue<std::uint32_t> tasks;
    std::queue<std::uint32_t> expected_results;
};

#endif // SIM_DUT_HPP