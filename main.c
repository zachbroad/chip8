#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "constants.h"
#include "chip8.h"
#include "operations.h"

void printHello();
void execute();
void loadProgramIntoMemory();

// instructions binary data
unsigned int instructions[] = {
        0x00000000, // 0x00: nop
        0x01234567, // 0x04: mov r0, 0x01234567
};




unsigned short opcode;


unsigned short V[16]; // registers
unsigned int memory[4096];
unsigned char gfx[64 * 32];

unsigned char delay_timer;
unsigned char sound_timer;

unsigned short stack[16];
unsigned short sp; // stack pointer

unsigned char key[16];

unsigned char chip8_fontset[80] =
        {
                0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };


//memory offsets
/*
  0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
  0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
  0x200-0xFFF - Program ROM and work RAM
 */

unsigned short const PROGRAM_RAM = 0x200;
unsigned short const INTERPRETER_RAM = 0x000;
unsigned short const DISPLAY_RAM = 0xF00;

unsigned short l;
unsigned short pc = PROGRAM_RAM;

unsigned short program[] = {
        0x0000,
};





int main() {
    printf("Starting emulator...\n");
    // init
    Chip8 chip8;

    chip8.pc = PROGRAM_RAM;

    // Main loop
    while (true) {
        chip8.opcode = memory[pc] << 8 | memory[pc + 1];
        execute(&chip8);
        chip8.pc += 2;

        usleep(10000); // wait
    }

    // Render

    return 0;
}

unsigned short getAddr(unsigned short opcode) 
{
    return opcode & 0x0FFF;
}

void execute(Chip8* chip8) {
    switch (chip8->opcode & 0xF000) { // CLS
    /*
        0nnn - SYS addr
        Jump to a machine code routine at nnn.
        This instruction is only used on the old computers on which Chip-8 was originally implemented. It is ignored by modern interpreters.

        00E0 - CLS
        00EE - RET*/
        case 0x0000:
            switch (chip8->opcode & 0x00FF) {
                case 0x00E0: // CLS
                    chip8_cls(&chip8);
                case 0x00EE: // RET
                    chip8_ret(&chip8);
                default:
                    chip8_sys(&chip8, getAddr(chip8->opcode));
            }
        case 0x1000: // JP addr
            chip8_jp(&chip8, getAddr(chip8->opcode))

    }
    printf("%d - %d\n", pc, opcode);
}


void printHello() {
    printf("Hello, World!\n");
}

