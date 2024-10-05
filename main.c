#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>

#include "chip8.h"
#include "constants.h"

#define DEBUG = 1

Chip8 chip8;
SDL_Window* window;

void chip8_FetchDecodeExecute(Chip8* chip8);
void chip8_LoadProgram(Chip8* chip8, char* program);
void chip8_InitDisplay(Chip8* chip8);
void chip8_InitSystem(Chip8* chip8);

unsigned short const PROGRAM_RAM     = 0x200;
unsigned short const INTERPRETER_RAM = 0x000;
unsigned short const DISPLAY_RAM     = 0xF00;

int main(void)
{
    printf("Starting emulator...\n");
    printf("Initializing Chip8...\n");

    chip8_InitSystem(&chip8);
    chip8_InitDisplay(&chip8);

    // Main loop
    while(true)
    {
        // Execute
        chip8_FetchDecodeExecute(&chip8);

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_EVENT_QUIT: return 0;
            }
        }

        // Add rendering code here

        usleep(10000); // Slow down execution
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void chip8_FetchDecodeExecute(Chip8* chip8)
{
    // Fetch
    chip8->opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];

    // Decode
    short nnn         = chip8->opcode & 0x0FFF;
    unsigned char x   = chip8->opcode & 0x0F00;
    unsigned char y   = chip8->opcode & 0x00F0;
    unsigned short kk = chip8->opcode & 0x00FF; // Byte
    unsigned char n   = chip8->opcode & 0x000F;

    // Execute
    switch(chip8->opcode & 0xF000)
    {
    case 0x0000: // 0nnn
        switch(chip8->opcode & 0x00FF)
        {
        case 0x00E0: // CLS - Clear the display
            printf("0x%04X: CLS\n", chip8->pc);
            chip8_cls(chip8);
            break;
        case 0x00EE: // RET - Return from a subroutine
            printf("0x%04X: RET\n", chip8->pc);
            chip8_ret(chip8);
            break;
        default: // SYS addr
            printf("0x%04X: SYS addr=0x%03X\n", chip8->pc, nnn);
            chip8_sys(chip8, nnn);
            break;
        }
        break;
    case 0x1000: // 1nnn - JP addr
        printf("0x%04X: JP addr=0x%03X\n", chip8->pc, nnn);
        chip8_jp(chip8, nnn);
        break;
    case 0x2000: // 2nnn - CALL addr
        printf("0x%04X: CALL addr=0x%03X\n", chip8->pc, nnn);
        chip8_call(chip8, nnn);
        break;
    case 0x3000: // 3xkk - SE Vx, byte
        printf("0x%04X: SE V%X, byte=0x%02X\n", chip8->pc, x, kk);
        chip8_se(chip8, x, kk);
        break;
    case 0x4000: // 4xkk - SNE Vx, byte
        printf("0x%04X: SNE V%X, byte=0x%02X\n", chip8->pc, x, kk);
        chip8_sne(chip8, x, kk);
        break;
    case 0x5000: // 5xy0 - SE Vx, Vy
        printf("0x%04X: SE V%X, V%X\n", chip8->pc, x, y);
        chip8_se(chip8, x, y);
        break;
    case 0x6000: // 6xkk - LD Vx, byte
        printf("0x%04X: LD V%X, byte=0x%02X\n", chip8->pc, x, kk);
        chip8_ld_vx_byte(chip8, x, kk);
        break;
    case 0x7000: // 7xkk - ADD Vx, byte
        printf("0x%04X: ADD V%X, byte=0x%02X\n", chip8->pc, x, kk);
        chip8_add_vx_byte(chip8, x, kk);
        break;
    case 0x8000: // 8xy? - LD Vx, Vy
        switch(chip8->opcode & 0x000F)
        {
        case 0x0: // 8xy0 - LD Vx, Vy
            printf("0x%04X: LD V%X, V%X\n", chip8->pc, x, y);
            chip8_ld_vx_vy(chip8, x, y);
            break;
        case 0x1: // 8xy1 - OR Vx, Vy
            printf("0x%04X: OR V%X, V%X\n", chip8->pc, x, y);
            chip8_or_vx_vy(chip8, x, y);
            break;
        case 0x2: // 8xy2 - AND Vx, Vy
            printf("0x%04X: AND V%X, V%X\n", chip8->pc, x, y);
            chip8_and_vx_vy(chip8, x, y);
            break;
        case 0x3: // 8xy3 - XOR Vx, Vy
            printf("0x%04X: XOR V%X, V%X\n", chip8->pc, x, y);
            chip8_xor_vx_vy(chip8, x, y);
            break;
        case 0x4: // 8xy4 - ADD Vx, Vy
            printf("0x%04X: ADD V%X, V%X\n", chip8->pc, x, y);
            chip8_add_vx_vy(chip8, x, y);
            break;
        case 0x5: // 8xy5 - SUB Vx, Vy
            printf("0x%04X: SUB V%X, V%X\n", chip8->pc, x, y);
            chip8_sub_vx_vy(chip8, x, y);
            break;
        case 0x6: // 8xy6 - SHR Vx, Vy
            printf("0x%04X: SHR V%X, V%X\n", chip8->pc, x, y);
            chip8_shr_vx_vy(chip8, x, y);
            break;
        case 0x7: // 8xy7 - SUBN Vx, Vy
            printf("0x%04X: SUBN V%X, V%X\n", chip8->pc, x, y);
            chip8_subn_vx_vy(chip8, x, y);
            break;
        case 0xE: // 8xyE - SHL Vx, Vy
            printf("0x%04X: SHL V%X, V%X\n", chip8->pc, x, y);
            chip8_shl_vx_vy(chip8, x, y);
            break;
        }
        break;
    case 0x9000: // 9xy0 - SNE Vx, Vy
        printf("0x%04X: SNE V%X, V%X\n", chip8->pc, x, y);
        chip8_sne_vx_vy(chip8, x, y);
        break;
    case 0xA000: // Annn - LD I, addr
        printf("0x%04X: LD I, addr=0x%03X\n", chip8->pc, nnn);
        chip8_ld_i_addr(chip8, nnn);
        break;
    case 0xB000: // Bnnn - JP V0, addr
        printf("0x%04X: JP V0, addr=0x%03X\n", chip8->pc, nnn);
        chip8_jp_v0_addr(chip8, nnn);
        break;
    case 0xC000: // Cxkk - RND Vx, byte
        printf("0x%04X: RND V%X, byte=0x%02X\n", chip8->pc, x, kk);
        chip8_rnd_vx_byte(chip8, x, kk);
        break;
    case 0xD000: // Dxyn - DRW Vx, Vy, nibble
        printf("0x%04X: DRW V%X, V%X, nibble=0x%X\n", chip8->pc, x, y, n);
        chip8_drw_vx_vy_nibble(chip8, x, y, n);
        break;
    case 0xE000: // Ex9E - SKP Vx
        printf("0x%04X: SKP V%X\n", chip8->pc, x);
        chip8_skp_vx(chip8, x);
        break;
    case 0xF000: // Fx07 - LD Vx, DT
        printf("0x%04X: LD V%X, DT\n", chip8->pc, x);
        chip8_ld_vx_dt(chip8, x);
        break;
    default:
        printf("0x%04X: Unknown opcode: 0x%04X\n", chip8->pc, chip8->opcode);
        break;
    }

    // Increment program counter
    chip8->pc += 2;
}

void chip8_InitSystem(Chip8* chip8)
{
    chip8->memory      = (unsigned char*) malloc(4096);
    chip8->V           = (unsigned char*) malloc(16);
    chip8->stack       = (unsigned short*) malloc(16);
    chip8->key         = (unsigned char*) malloc(16);
    chip8->gfx         = (unsigned char*) malloc(64 * 32);
    chip8->pc          = 0;
    chip8->I           = 0;
    chip8->sp          = 0;
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
    chip8->opcode      = 0;
    chip8->pc          = PROGRAM_RAM;

    // Clear the display
    for(int i = 0; i < SCREEN_SIZE; i++)
    {
        chip8->gfx[i] = 0;
    }
}

void chip8_loadProgram(Chip8* chip8, char* program)
{
    // Load program
    printf("Loading program...\n");
    FILE* filePtr;
    filePtr = fopen("particle.ch8", "rb");
    char buffer[3584];
    fgets(buffer, 3584, filePtr);

    for(int i = 0; i < 3584; i++)
    {
        chip8->memory[PROGRAM_RAM + i] = program[i];
    }
}

void chip8_InitDisplay(Chip8* chip8)
{
    SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
    // Initialize SDL
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("CHIP8",       // window title
                              SCREEN_WIDTH,  // width, in pixels
                              SCREEN_HEIGHT, // height, in pixels
                              SDL_WINDOW_OPENGL | SDL_WINDOW_ALWAYS_ON_TOP // flags - see below
    );

    // Check that the window was successfully created
    if(window == NULL)
    {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                     SDL_GetError());
        exit(1);
    }
    else
    {
        printf("Window created\n");
        // The window was successfully created, so show it
        SDL_ShowWindow(window);
    }
}
