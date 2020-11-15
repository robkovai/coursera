cmake_minimum_required(VERSION 3.5)

project(project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("tests/" ".")

set(TESTS tests/tests.cpp tests/tests.h tests/test_runner.cpp tests/test_runner.h
    tests/date_test.cpp tests/date_test.h
    tests/condition_parser_test.cpp tests/condition_parser_test.h
    tests/event_parser_test.cpp tests/event_parser_test.h
    tests/database_test.cpp tests/database_test.h)

add_executable(project ${TESTS} main.cpp token.cpp token.h condition_parser.cpp condition_parser.h
     date.cpp date.h database.cpp database.h node.cpp node.h event.cpp event.h)
