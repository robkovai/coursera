cmake_minimum_required(VERSION 3.5)

project(part4_week1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)

add_executable(part4_week1_lesson01 lesson_01.cpp ${TEST_RUNNER})
add_executable(part4_week1_lesson02 lesson_02.cpp ${TEST_RUNNER})
add_executable(part4_week1_lesson03 lesson_03.cpp ${TEST_RUNNER})
add_executable(part4_week1_lesson04 lesson_04.cpp ${TEST_RUNNER})
add_executable(part4_week1_lesson05 lesson_05.cpp ${TEST_RUNNER})
add_executable(part4_week1_lesson06 lesson_06.cpp ${TEST_RUNNER})
