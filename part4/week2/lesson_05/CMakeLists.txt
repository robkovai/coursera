cmake_minimum_required(VERSION 3.5)

project(part4_week2_lesson05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

include_directories(..)

set(TEST_RUNNER ../test_runner.cpp ../test_runner.h)

add_executable(part4_week2_lesson05 main.cpp stats_aggregator.cpp stats_aggregator.h stats_aggregator_test.cpp ${TEST_RUNNER})
