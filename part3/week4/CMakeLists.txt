cmake_minimum_required(VERSION 3.5)

project(week4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)
set(PROFILER profile.h)

add_executable(lesson01 lesson_01.cpp ${TEST_RUNNER} ${PROFILER})
add_executable(lesson02 lesson_02.cpp ${TEST_RUNNER} ${PROFILER} stack_vector.h)
add_executable(lesson03 lesson_03.cpp ${TEST_RUNNER} ${PROFILER})
add_executable(lesson04 lesson_04.cpp ${TEST_RUNNER} ${PROFILER})
add_executable(lesson05 lesson_05.cpp ${TEST_RUNNER} ${PROFILER})
add_executable(lesson06 lesson_06.cpp ${TEST_RUNNER} ${PROFILER} stats.h stats.cpp http_request.h)
