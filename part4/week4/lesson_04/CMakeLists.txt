cmake_minimum_required(VERSION 3.5)

project(part4_week4_lesson04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

include_directories(..)

set(TEST_RUNNER ../test_runner.cpp ../test_runner.h)

add_executable(part4_week4_lesson04 main.cpp old_booking_providers.h old_trip_manager.h new_booking_providers.h new_trip_manager.h booking.h ${TEST_RUNNER})
