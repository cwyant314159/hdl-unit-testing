add_library(test_infra STATIC)
target_sources(test_infra PRIVATE main.cpp)
target_include_directories(test_infra PUBLIC include)
target_link_libraries(test_infra PUBLIC GTest::gtest)

# Workaround for weakly defined symbols inside verilator libraries on MacOS
if(APPLE)
    target_link_options(test_infra PUBLIC "-Wl,-flat_namespace,-undefined,dynamic_lookup")
endif()
