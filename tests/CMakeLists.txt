cmake_minimum_required(VERSION 3.16)
project(UnitTests LANGUAGES CXX)

# Find GoogleTest package
find_package(GTest REQUIRED)

# Glob all test source files
file(GLOB TEST_SOURCES "*.cpp")

# Create the test executable
add_executable(unit_tests ${TEST_SOURCES})

# Link against the Conan-provided GoogleTest target
target_link_libraries(unit_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
