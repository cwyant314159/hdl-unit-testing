#include <cstdint>
#include <gtest/gtest.h>

#include "sim_dut.hpp"

class ControlDeviceFixture : public ::testing::Test
{
    virtual void SetUp()
    {
        const std::string test_name =
            ::testing::UnitTest::GetInstance()->current_test_info()->name();

        const std::string suite_name =
            ::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();

        p_dut = new SimDut(suite_name, test_name);
        p_dut->reset(5);
    }

    virtual void TearDown()
    {
        delete p_dut;
    }

protected:
    SimDut *p_dut;

    void loopOp(SimDut::Operations op)
    {
        for (size_t a = 0; a <= 0xFF; a += 1) {
            for (size_t b = 0; b <= 0xFF; b += 1) {
                p_dut->enqueueOperation(op, a, b);
            }
        }
    }
};

TEST_F(ControlDeviceFixture, AndOperation)
{
    loopOp(SimDut::Operations::OP_AND);
    p_dut->evaluate();
}

TEST_F(ControlDeviceFixture, OrOperation)
{
    loopOp(SimDut::Operations::OP_OR);
    p_dut->evaluate();
}

TEST_F(ControlDeviceFixture, XorOperation)
{
    loopOp(SimDut::Operations::OP_XOR);
    p_dut->evaluate();
}

TEST_F(ControlDeviceFixture, NotAOperation)
{
    loopOp(SimDut::Operations::OP_NOT_A);
    p_dut->evaluate();
}

TEST_F(ControlDeviceFixture, NndOperation)
{
    loopOp(SimDut::Operations::OP_NAND);
    p_dut->evaluate();
}

TEST_F(ControlDeviceFixture, NorOperation)
{
    loopOp(SimDut::Operations::OP_NOR);
    p_dut->evaluate();
}

TEST_F(ControlDeviceFixture, XnorOperation)
{
    loopOp(SimDut::Operations::OP_XNOR);
    p_dut->evaluate();
}

TEST_F(ControlDeviceFixture, NotBOperation)
{
    loopOp(SimDut::Operations::OP_NOT_B);
    p_dut->evaluate();
}