cmake_minimum_required(VERSION 3.27)
project(chip8)

set(CMAKE_CXX_STANDARD 23)

add_executable(chip8 main.cpp)
target_link_libraries(chip8 SDL)