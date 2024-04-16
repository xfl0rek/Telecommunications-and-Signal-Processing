cmake_minimum_required(VERSION 3.27)
project(Exercise1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")


add_executable(Exercise1 src/main.cpp
        include/matrix.h
        include/algorithm.h
        src/algorithm.cpp)
