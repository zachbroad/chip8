cmake_minimum_required(VERSION 3.5)
project(chip8)

add_subdirectory(SDL EXCLUDE_FROM_ALL)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/roms/particle.ch8 ${CMAKE_CURRENT_BINARY_DIR}/particle.ch8 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/roms/zero.ch8 ${CMAKE_CURRENT_BINARY_DIR}/zero.ch8 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/roms/ibm.ch8 ${CMAKE_CURRENT_BINARY_DIR}/ibm.ch8 COPYONLY)
add_executable(chip8 main.c chip8.c constants.c)

if(TARGET SDL2::SDL2main)
    target_link_libraries(chip8 PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(chip8 PRIVATE SDL2::SDL2)
