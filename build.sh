#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Configure CMake
cmake ..

# Build the project
cmake --build .

# Run the executable
./chip8

# Return to the original directory
cd ..
