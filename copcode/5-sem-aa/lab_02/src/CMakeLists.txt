cmake_minimum_required(VERSION 3.19)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp Matrix/MatrixError.cpp Matrix/MatrixError.h Matrix/Matrix.cpp Matrix/Matrix.h)