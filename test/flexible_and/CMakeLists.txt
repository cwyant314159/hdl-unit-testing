#
# Flexible AND Gate test application
#
add_executable(test_flexible_and)
target_include_directories(test_flexible_and PRIVATE include)
target_sources(test_flexible_and PRIVATE
    environment.cpp
    flexible_and_tests.cpp
)
target_link_libraries(test_flexible_and verilated_flexible_and test_infra)
add_test(NAME test_flexible_and COMMAND test_flexible_and)