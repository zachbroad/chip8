#include "constants.h"

/* Notes on Chip8
 *
 * Each instruction is 2 bytes long
 * Instructions are big-endian. 35 instructions
 * Programs are loaded into memory starting at 0x200
 *
 * Memory addresses 0x000 to 0x1FF are reserved for the interpreter
 * Final 352 bytes of memory are reserved for the display
 *
 * This leaves 0x200 to 0x69f free for programs to use
 *
 * Chip8 has 16 8-bit V (V0 to VF)
 * Capable of storing unsigned integer values between 0x00 and 0xff
 *
 *
 * Graphics output is 64x32 pixels
 * Each pixel can be on or off - monochrome
 *
 * */

typedef struct {
    unsigned short pc; // Program counter
    unsigned short opcode; // Current opcode
    unsigned short stack[16]; // Stack
    unsigned short sp; // Stack pointer
    unsigned short I; // Index register
    unsigned short delay_timer; // Delay timer
    unsigned short sound_timer; // Sound timer
    unsigned char V[16]; // Registers
    unsigned char gfx[SCREEN_SIZE]; // Graphics
    unsigned int memory[4096]; // Memory
    unsigned char key[16]; // Keyboard
} Chip8;