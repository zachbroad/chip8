cmake_minimum_required(VERSION 3.5)
project(chip8)

# Create an option to switch between a system sdl library and a vendored sdl library
#option(MYGAME_VENDORED "Use vendored libraries" ON)

#if(MYGAME_VENDORED)
add_subdirectory(SDL EXCLUDE_FROM_ALL)
#else()
#    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2-shared)
#endif()

# Create your game executable target as usual
# Add particle.ch8 as a resource file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/particle.ch8 ${CMAKE_CURRENT_BINARY_DIR}/particle.ch8 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/zero.ch8 ${CMAKE_CURRENT_BINARY_DIR}/zero.ch8 COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ibm.ch8 ${CMAKE_CURRENT_BINARY_DIR}/ibm.ch8 COPYONLY)

add_executable(chip8 main.c chip8.c constants.c)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(chip8 PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL library.
target_link_libraries(chip8 PRIVATE SDL2::SDL2)
