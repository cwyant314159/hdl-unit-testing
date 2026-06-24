#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "environment.hpp"

struct ControlConfig {
    bool invert_a = false;
    bool invert_b = false;
    bool invert_y = false;
};

class FlexibleAndFixture : public ::testing::TestWithParam<ControlConfig>
{
    void SetUp() override
    {
        const std::string test_name =
            ::testing::UnitTest::GetInstance()->current_test_info()->name();

        const std::string suite_name =
            ::testing::UnitTest::GetInstance()->current_test_info()->test_suite_name();

        // Build the test case name from the gtest data and replace invalid
        // file name characters.
        std::string testCaseName = suite_name + '_' + test_name;
        std::replace(testCaseName.begin(), testCaseName.end(), '/', '_');

        p_env = std::make_unique<Environment>(testCaseName);
        p_env->ResetDut(5);
    }

protected:
    std::unique_ptr<Environment> p_env;

};

TEST_P(FlexibleAndFixture, DutOperations)
{
    const ControlConfig  cfg  = GetParam();
    const ControlDriver& ctrl = p_env->GetControl();
    ctrl.invert_a(cfg.invert_a);
    ctrl.invert_b(cfg.invert_b);
    ctrl.invert_y(cfg.invert_y);

    for (std::uint8_t a = 0; a < 0x0F; ++a) {
        for (std::uint8_t b = 0; b < 0x0F; ++b) {
            p_env->EnqueueTransaction(a, b);
        }
    }

    p_env->EnqueueTransaction(0x00, 0x00);
    p_env->EnqueueTransaction(0x00, 0x0F);
    p_env->EnqueueTransaction(0x00, 0xF0);
    p_env->EnqueueTransaction(0x00, 0xFF);
    p_env->EnqueueTransaction(0x0F, 0x00);
    p_env->EnqueueTransaction(0x0F, 0x0F);
    p_env->EnqueueTransaction(0x0F, 0xF0);
    p_env->EnqueueTransaction(0x0F, 0xFF);
    p_env->EnqueueTransaction(0xF0, 0x00);
    p_env->EnqueueTransaction(0xF0, 0x0F);
    p_env->EnqueueTransaction(0xF0, 0xF0);
    p_env->EnqueueTransaction(0xF0, 0xFF);
    p_env->EnqueueTransaction(0xFF, 0x00);
    p_env->EnqueueTransaction(0xFF, 0x0F);
    p_env->EnqueueTransaction(0xFF, 0xF0);
    p_env->EnqueueTransaction(0xFF, 0xFF);

    p_env->Run();
}

INSTANTIATE_TEST_SUITE_P(
    ControlConfig,
    FlexibleAndFixture,
    ::testing::Values(
        ControlConfig{false, false, false}, //    A &  B
        ControlConfig{false, false, true},  // ~( A &  B)
        ControlConfig{true,  false, false}, //   ~A &  B
        ControlConfig{true,  false, true}, //  ~(~A &  B)
        ControlConfig{false, true,  false}, //    A & ~B
        ControlConfig{false, true,  true}, //  ~( A & ~B)
        ControlConfig{true,  true,  false}, //   ~A & ~B
        ControlConfig{true,  true,  true}   // ~(~A & ~B)
    )
);