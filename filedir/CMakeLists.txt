cmake_minimum_required(VERSION 3.15)
project(filedir C)

set(CMAKE_C_STANDARD 99)

include_directories(../apue/include)
link_directories(../apue/lib)
link_libraries(apue)

add_executable(filetype filetype.c)
add_executable(access access.c)
add_executable(umask umask.c)
add_executable(changmod changmod.c)
add_executable(unlink unlink.c)
add_executable(zap zap.c)
add_executable(ftw ftw.c)