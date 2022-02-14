cmake_minimum_required(VERSION 3.20)
project(LR5d C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(libs)

add_executable(LR5d main.c)
