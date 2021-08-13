cmake_minimum_required(VERSION 3.5)

project(part4_week5_lesson06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER ../test_runner.cpp ../test_runner.h)

include_directories(..)

add_executable(part4_week5_lesson06_tests tests.cpp solution.h ${TEST_RUNNER})
add_executable(part4_week5_lesson06_bug1 bug1_bad.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson06_bug2 bug2_bad.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson06_bug3 bug3_bad.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson06_bug4 bug4_bad.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson06_bug5 bug5_bad.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson06_bug6 bug6_bad.cpp ${TEST_RUNNER})
