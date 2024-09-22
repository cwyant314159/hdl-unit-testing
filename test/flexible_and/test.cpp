#include <cstdint>
#include <gtest/gtest.h>

#include "sim_dut.hpp"

class FlexibleAndFixture : public ::testing::Test
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

};

TEST_F(FlexibleAndFixture, RegularAndOperations)
{
    Transaction t;

    t.a = 0x55;
    t.a = 0xAA;
    p_dut->enqueueTransaction(t);

    t.a = 0x34;
    t.b = 0x0F;
    p_dut->enqueueTransaction(t);

    t.a = 0x00;
    t.b = 0xFF;
    p_dut->enqueueTransaction(t);

    p_dut->evaluate();
}

TEST_F(FlexibleAndFixture, RegularNndOperations)
{
    Transaction t;

    t.invert_y = true;

    t.a = 0x55;
    t.a = 0xAA;
    p_dut->enqueueTransaction(t);

    t.a = 0x34;
    t.b = 0x0F;
    p_dut->enqueueTransaction(t);

    t.a = 0x00;
    t.b = 0xFF;
    p_dut->enqueueTransaction(t);

    p_dut->evaluate();
}

TEST_F(FlexibleAndFixture, InvertAOnlyOperations)
{
    Transaction t;

    t.invert_a = true;

    t.a = 0x55;
    t.a = 0xAA;
    p_dut->enqueueTransaction(t);

    t.a = 0x34;
    t.b = 0x0F;
    p_dut->enqueueTransaction(t);

    t.a = 0x00;
    t.b = 0xFF;
    p_dut->enqueueTransaction(t);

    p_dut->evaluate();
}

TEST_F(FlexibleAndFixture, InvertBOnlyOperations)
{
    Transaction t;

    t.invert_b = true;

    t.a = 0x55;
    t.a = 0xAA;
    p_dut->enqueueTransaction(t);

    t.a = 0x34;
    t.b = 0x0F;
    p_dut->enqueueTransaction(t);

    t.a = 0x00;
    t.b = 0xFF;
    p_dut->enqueueTransaction(t);

    p_dut->evaluate();
}

TEST_F(FlexibleAndFixture, InvertAAndBOperations)
{
    Transaction t;

    t.invert_a = true;
    t.invert_b = true;

    t.a = 0x55;
    t.a = 0xAA;
    p_dut->enqueueTransaction(t);

    t.a = 0x34;
    t.b = 0x0F;
    p_dut->enqueueTransaction(t);

    t.a = 0x00;
    t.b = 0xFF;
    p_dut->enqueueTransaction(t);

    p_dut->evaluate();
}