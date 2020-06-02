cmake_minimum_required(VERSION 3.16)
project(stdio C)

set(CMAKE_C_STANDARD 99)

include_directories(../apue/include)
link_directories(../apue/lib)
link_libraries(apue)

add_executable(stdio buf.c)