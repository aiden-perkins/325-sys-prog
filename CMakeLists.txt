cmake_minimum_required(VERSION 3.28)
project(325_sys_prog)

set(CMAKE_CXX_STANDARD 14)

include_directories("Prog 0")
include_directories("Prog 1")
include_directories("Prog 2")
set(SOURCE_FILES "Prog 0/fibo.cpp" "Prog 1/war.cpp" "Prog 2/war.cpp")

add_executable(Prog0 "Prog 0/fibo.cpp")
add_executable(Prog1 "Prog 1/Card.cpp" "Prog 1/Card.h" "Prog 1/Deck.cpp" "Prog 1/Deck.h" "Prog 1/war.cpp")
add_executable(Prog2 "Prog 2/war.cpp")
