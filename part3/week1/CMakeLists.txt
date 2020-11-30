cmake_minimum_required(VERSION 3.5)

project(week1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)

add_executable(lesson01 lesson_01.cpp ${TEST_RUNNER})
add_executable(lesson02 lesson_02.cpp ${TEST_RUNNER})
add_executable(lesson03 lesson_03.cpp ${TEST_RUNNER} airline_ticket.h)
add_executable(lesson04 lesson_04.cpp ${TEST_RUNNER} airline_ticket.h)
add_executable(lesson05 lesson_05.cpp ${TEST_RUNNER})
add_executable(lesson06 lesson_06.cpp)
add_executable(lesson07 lesson_07.cpp ${TEST_RUNNER})
add_executable(lesson08 lesson_08.cpp ${TEST_RUNNER})
add_executable(lesson09 lesson_09.cpp ${TEST_RUNNER})
