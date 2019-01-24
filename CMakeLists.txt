cmake_minimum_required(VERSION 3.13)
project(nuklear_cross)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -I/usr/local/lib -framework OpenGL -lglfw")

add_executable(nuklear_cross main.cpp nuklear_cross.c)