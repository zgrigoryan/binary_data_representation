cmake_minimum_required(VERSION 3.10)
project(binary_data_representation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(my_program detecting_endianness.cpp)
