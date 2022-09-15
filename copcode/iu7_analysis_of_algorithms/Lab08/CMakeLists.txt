cmake_minimum_required(VERSION 3.12)
project(Lab08)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab08
        BM.h
        KMP.h
        main.cpp)
