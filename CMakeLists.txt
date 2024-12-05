cmake_minimum_required(VERSION 3.26)
project(DM C)

set(CMAKE_C_STANDARD 11)

add_executable(DM
        src/main.c
        src/mazeGenerator.c
        includes/mazeGenerator.h
        src/mazeSolver.c
        includes/maze.h
        src/maze.c
        includes/mazeSolver.h)

find_package(raylib REQUIRED)

if (raylib_FOUND)
    include_directories(${raylib_INCLUDE_DIRS})
    target_link_libraries(DM ${raylib_LIBRARIES})
else()
    message(FATAL_ERROR "Raylib n'a pas été trouvé.")
endif()