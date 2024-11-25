cmake_minimum_required(VERSION 3.26)
project(DM C)

set(CMAKE_C_STANDARD 11)

add_executable(DM
        src/main.c
        src/mazeGenerator.c)
