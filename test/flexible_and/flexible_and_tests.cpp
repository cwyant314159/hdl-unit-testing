#include <cstdint>
#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "environment.hpp"

class FlexibleAndFixture : public ::testing::Test
{
    void SetUp() override
    {
        const std::string test_name =
            ::testing::UnitTest::GetInstance()->current_test_info()->name();

        const std::string suite_name =
            ::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();

        const std::string testCaseName = suite_name + '_' + test_name;

        p_env = std::make_unique<Environment>(testCaseName);
        p_env->ResetDut(5);
    }

protected:
    std::unique_ptr<Environment> p_env;

};

TEST_F(FlexibleAndFixture, RegularAndOperations)
{
    p_env->EnqueueTransaction(0x55, 0xAA);
    p_env->EnqueueTransaction(0x34, 0x0F);
    p_env->EnqueueTransaction(0x00, 0xFF);
    p_env->Run();
}

TEST_F(FlexibleAndFixture, RegularNandOperations)
{
    const ControlDriver& ctrl = p_env->GetControl();

    ctrl.invert_y(true);
    p_env->EnqueueTransaction(0x55, 0xAA);
    p_env->EnqueueTransaction(0x34, 0x0F);
    p_env->EnqueueTransaction(0x00, 0xFF);
    p_env->Run();
}

TEST_F(FlexibleAndFixture, InvertAOnlyOperations)
{
    const ControlDriver& ctrl = p_env->GetControl();

    ctrl.invert_a(true);
    p_env->EnqueueTransaction(0x55, 0xAA);
    p_env->EnqueueTransaction(0x34, 0x0F);
    p_env->EnqueueTransaction(0x00, 0xFF);
    p_env->Run();
}

TEST_F(FlexibleAndFixture, InvertBOnlyOperations)
{
    const ControlDriver& ctrl = p_env->GetControl();

    ctrl.invert_b(true);
    p_env->EnqueueTransaction(0x55, 0xAA);
    p_env->EnqueueTransaction(0x34, 0x0F);
    p_env->EnqueueTransaction(0x00, 0xFF);
    p_env->Run();
}

TEST_F(FlexibleAndFixture, InvertAAndBOperations)
{
    const ControlDriver& ctrl = p_env->GetControl();

    ctrl.invert_a(true);
    ctrl.invert_b(true);
    p_env->EnqueueTransaction(0x55, 0xAA);
    p_env->EnqueueTransaction(0x34, 0x0F);
    p_env->EnqueueTransaction(0x00, 0xFF);
    p_env->Run();
}