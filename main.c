#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "chip8.h"

//memory offsets
/*
  0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
  0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
  0x200-0xFFF - Program ROM and work RAM
 */

unsigned short const PROGRAM_RAM = 0x200;
unsigned short const INTERPRETER_RAM = 0x000;
unsigned short const DISPLAY_RAM = 0xF00;

void execute(Chip8* chip8);
unsigned short getAddr(unsigned short opcode);

unsigned int instructions[] = {
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x00000000, // 0x00: nop
        0x01234567, // 0x04: mov r0, 0x01234567
};


unsigned short getAddr(unsigned short opcode) 
{
    return opcode & 0x0FFF;
}

int main() {
    printf("Starting emulator...\n");

    printf("Initializing Chip8...\n");

    Chip8 chip8;
    chip8.memory = (unsigned char*) malloc(4096);
    chip8.V = (unsigned char*) malloc(16);
    chip8.stack = (unsigned short*) malloc(16);
    chip8.key = (unsigned char*) malloc(16);
    chip8.gfx = (unsigned char*) malloc(64 * 32);
    chip8.pc = 0;
    chip8.I = 0;
    chip8.sp = 0;
    chip8.delay_timer = 0;
    chip8.sound_timer = 0;
    chip8.opcode = 0;


    // Load program
    printf("Loading program...\n");
    FILE* filePtr;
    filePtr = fopen("particle.ch8", "rb");
    char buffer[3584];
    fgets(buffer, 3584, filePtr);

    // Load into memory
    for (int i = 0; i < 3584; i++) {
        chip8.memory[PROGRAM_RAM + i] = buffer[i];
    }

    chip8.pc = PROGRAM_RAM;
    printf("PC: %d\n", chip8.pc);

    // Main loop
    while (true) {
        // Execute
        chip8.opcode = chip8.memory[chip8.pc] << 8 | chip8.memory[chip8.pc + 1];
        execute(&chip8);
        chip8.pc += 2;

        usleep(10000); // wait
        

        // Render

    }

    return 0;
}

void execute(Chip8* chip8) {
    printf("%d - %d\n", chip8->pc, chip8->opcode);

    switch (chip8->opcode & 0xF000) { // CLS
        case 0x0000:
            switch (chip8->opcode & 0x00FF) {
                case 0x00E0: // CLS
                    chip8_cls(chip8);
                case 0x00EE: // RET
                    chip8_ret(chip8);
                default: // SYS
                    chip8_sys(chip8, getAddr(chip8->opcode));
            }
        case 0x1000: // JP addr
            chip8_jp(chip8, getAddr(chip8->opcode));
    }
}

