cmake_minimum_required(VERSION 3.12)
project(Matr)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matr main.cpp matrix.h Winograd.h)