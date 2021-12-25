cmake_minimum_required(VERSION 3.20)
project(mycomp C)

set(CMAKE_C_STANDARD 90)

add_executable(mycomp mycomp.c complex.c complex.h complex.c complex_tester.c complex_tester.c command.c command.h string_manipulations.c string_manipulations.h mycomp.h)
target_link_libraries(mycomp m)