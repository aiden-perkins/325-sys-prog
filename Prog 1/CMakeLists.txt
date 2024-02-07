cmake_minimum_required(VERSION 3.28)
project(Prog_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Prog_1
        Card.cpp
        Card.h
        Deck.cpp
        Deck.h
        main.cpp)
