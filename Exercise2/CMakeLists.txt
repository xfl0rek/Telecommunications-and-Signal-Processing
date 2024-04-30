cmake_minimum_required(VERSION 3.24)
project(Exercise2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")


add_executable(Exercise2
        src/main.cpp
        include/receiver.h
        src/receiver.cpp
        include/transmitter.h
        src/transmitter.cpp
        src/port.cpp
        include/port.h)
