cmake_minimum_required(VERSION 3.5)

project(part4_week5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)
set(PROFILER profile.h)

add_subdirectory(lesson_01)
add_executable(part4_week5_lesson02 lesson_02.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson03 lesson_03.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson04 lesson_04.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson05 lesson_05.cpp ${TEST_RUNNER} ${PROFILER})
add_subdirectory(lesson_06)
add_executable(part4_week5_lesson07 lesson_07.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson08 lesson_08.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson09 lesson_09.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson10 lesson_10.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson11 lesson_11.cpp ${TEST_RUNNER})
add_executable(part4_week5_lesson12 lesson_12.cpp ${TEST_RUNNER})
