cmake_minimum_required(VERSION 3.15)
project(intro C)

set(CMAKE_C_STANDARD 99)

include_directories(../apue/include)
link_directories(../apue/lib)
link_libraries(apue)

add_executable(getcputc getcputc.c)
add_executable(ls ls.c)
add_executable(mycat mycat.c)
add_executable(shell shell.c)
add_executable(testerror testerror.c)
add_executable(uidgid uidgid.c)