cmake_minimum_required(VERSION 3.5)

project(part4_week4_lesson01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

include_directories(..)

set(TEST_RUNNER ../test_runner.cpp ../test_runner.h)

add_executable(part4_week4_lesson01 main.cpp Common.h Textures.h Textures.cpp Solution.cpp ${TEST_RUNNER})
