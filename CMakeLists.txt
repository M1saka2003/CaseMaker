cmake_minimum_required(VERSION 4.0)
project(CaseMaker)

set(CMAKE_CXX_STANDARD 26)

add_executable(CaseMaker main.cpp
        core/integer.hpp
        case/array.hpp
)
