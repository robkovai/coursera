cmake_minimum_required(VERSION 3.5)

project(lesson_04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lesson_04 main.cpp query.cpp query.h responses.cpp responses.h bus_manager.cpp bus_manager.h)
