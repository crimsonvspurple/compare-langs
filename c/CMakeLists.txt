cmake_minimum_required(VERSION 3.22)
project(c C)

set(CMAKE_C_STANDARD 23)

MATH(EXPR stack_size "1024 * 1024 * 1024") # 1024 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_executable(c main.c)
