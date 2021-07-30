cmake_minimum_required(VERSION 3.5)

project(week6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)
set(PROFILER profile.h)

add_executable(lesson01 main.cpp paginator.h synhronized.h search_server.h search_server.cpp parse.h parse.cpp ${TEST_RUNNER} ${PROFILER})
