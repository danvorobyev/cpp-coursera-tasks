cmake_minimum_required(VERSION 3.17)
project(week6)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(week6
    condition_parser.cc
    condition_parser.h
    condition_parser_test.cc
    database.cc
    database.h
    database_test.cc
    date.cc
    date.h
    date_test.cc
    main.cc
    node.cc
    node.h
    node_test.cc
    test_runner.h
    token.cc
    token.h)
