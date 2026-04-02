# chip8

A CHIP-8 emulator written in C using SDL2 for rendering and input.

## Features

- Full implementation of all 35 CHIP-8 opcodes with fetch-decode-execute cycle
- 64x32 monochrome display rendered via SDL2 with hardware-accelerated scaling
- Keyboard input mapped to the original CHIP-8 hex keypad layout
- Delay and sound timer support at 60 Hz
- Bundled ROMs (IBM Logo, Zero Demo, Particle) with an interactive ROM selection prompt

## Tech Stack

- **Language:** C
- **Graphics/Input:** SDL2
- **Build System:** CMake

## Getting Started

### Prerequisites

- CMake 3.5+
- A C compiler (gcc, clang, etc.)
- SDL2 is included as a Git submodule -- no system-wide install required

### Build and Run

```sh
mkdir -p build
cd build
cmake ..
cmake --build .
./chip8
```

Or use the provided script:

```sh
./build.sh
```

The emulator will prompt you to select a ROM on startup.

### Controls

The CHIP-8 hex keypad is mapped to the keyboard as follows:

```
CHIP-8 Key    Keyboard
---------     --------
1 2 3 C       1 2 3 4
4 5 6 D       Q W E R  /  A S D F
7 8 9 E       Q W E R
A 0 B F       Z X C V
```
