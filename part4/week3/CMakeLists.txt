cmake_minimum_required(VERSION 3.5)

project(part4_week3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)
set(PROFILER profile.h)

add_executable(part4_week3_lesson01 lesson_01.cpp ${TEST_RUNNER})
add_executable(part4_week3_lesson02 lesson_02.cpp ${TEST_RUNNER})
add_executable(part4_week3_lesson03 lesson_03.cpp ${TEST_RUNNER})
add_executable(part4_week3_lesson04 lesson_04.cpp ${TEST_RUNNER} ${PROFILER})
add_executable(part4_week3_lesson05 lesson_05.cpp ${TEST_RUNNER} ${PROFILER})
add_executable(part4_week3_lesson06 lesson_06.cpp ${TEST_RUNNER})
add_executable(part4_week3_lesson07 lesson_07.cpp ${TEST_RUNNER} animals.h)
add_executable(part4_week3_lesson08 lesson_08.cpp ${TEST_RUNNER})
add_executable(part4_week3_lesson09 lesson_09.cpp ${TEST_RUNNER} Common.h)
