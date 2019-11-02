cmake_minimum_required(VERSION 3.14)
project(fileio C)

set(CMAKE_C_STANDARD 99)

include_directories(../apue/include)
link_directories(../apue/lib)
link_libraries(apue)

add_executable(mycat mycat.c)
add_executable(seek seek.c)