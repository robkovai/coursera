cmake_minimum_required(VERSION 3.5)

project(part4_week4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)

add_subdirectory(lesson_01)
add_subdirectory(lesson_02)
add_executable(part4_week4_lesson03 lesson_03.cpp ${TEST_RUNNER})
add_subdirectory(lesson_04)
