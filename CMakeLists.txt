cmake_minimum_required(VERSION 3.20)
project(mycomp C)

set(CMAKE_C_STANDARD 90)

add_executable(mycomp mycomp.c complex.c complex.h complex_tester.c complex_tester.c)
target_link_libraries(mycomp m)