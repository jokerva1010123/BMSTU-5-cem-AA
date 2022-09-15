cmake_minimum_required(VERSION 3.12)
project(cmake_build_debug)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake_build_debug
        cmake_install.cmake
        CMakeCache.txt
        Lab08
        Lab08.cbp
        Makefile)
