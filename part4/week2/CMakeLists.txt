cmake_minimum_required(VERSION 3.5)

project(part4_week2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DDEBUG)

set(TEST_RUNNER test_runner.cpp test_runner.h)
set(XML xml.cpp xml.h)
set(JSON json.cpp json.h)
set(INI ini.cpp ini.h)

add_executable(part4_week2_lesson01 lesson_01.cpp ${TEST_RUNNER} ${XML})
add_executable(part4_week2_lesson02 lesson_02.cpp ${TEST_RUNNER} ${JSON})
add_executable(part4_week2_lesson03 lesson_03.cpp ${TEST_RUNNER} ${INI})
add_executable(part4_week2_lesson04 lesson_04.cpp ${TEST_RUNNER} ${XML} ${JSON})
add_subdirectory(lesson_05)
add_subdirectory(lesson_06)
add_executable(part4_week2_lesson07 lesson_07.cpp ${TEST_RUNNER})
