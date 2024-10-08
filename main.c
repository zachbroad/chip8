#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "SDL_events.h"
#include "SDL_stdinc.h"
#include "chip8.h"
#include "constants.h"

Chip8 chip8;
SDL_Window* window;
SDL_Texture* canvas;
SDL_Renderer* renderer;

void chip8_FetchDecodeExecute(Chip8* chip8);
void chip8_InitDisplay(Chip8* chip8);
void chip8_InitSystem(Chip8* chip8);
void chip8_LoadProgram(Chip8* chip8, char* program);
void chip8_RenderLoop(void);

unsigned short const INTERPRETER_RAM = 0x000;
unsigned short const PROGRAM_RAM     = 0x200;
unsigned short const DISPLAY_RAM     = 0xF00;
unsigned short const SCALE_FACTOR    = 10;

int main(void)
{
    printf("Starting emulator...\n");
    printf("Initializing Chip8...\n");

    chip8_InitSystem(&chip8);
    chip8_LoadProgram(&chip8, "ibm.ch8");
    chip8_InitDisplay(&chip8);

    const Uint32 TARGET_FRAME_TIME = 1000 / 60;
    Uint32 lastTimerUpdate         = SDL_GetTicks();

    // Main loop
    while(true)
    {
        // Execute
        chip8_FetchDecodeExecute(&chip8);
        chip8_RenderLoop();

        Uint32 currentTime = SDL_GetTicks();
        if(currentTime - lastTimerUpdate >= TARGET_FRAME_TIME)
        {
            if(chip8.delay_timer > 0)
            {
                chip8.delay_timer--;
            }
            if(chip8.sound_timer > 0)
            {
                if(chip8.sound_timer == 1)
                {
                    printf("BEEP!\n"); // TODO: Implement sound
                }
                chip8.sound_timer--;
            }

            lastTimerUpdate = currentTime;
        }
        usleep(10000); // Slow down execution
    }

    // Cleanup
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

void chip8_FetchDecodeExecute(Chip8* chip8)
{
    // Fetch
    chip8->opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];

    // Decode
    short nnn        = chip8->opcode & 0x0FFF;
    unsigned char x  = (chip8->opcode & 0x0F00) >> 8;
    unsigned char y  = (chip8->opcode & 0x00F0) >> 4;
    unsigned char kk = chip8->opcode & 0x00FF; // Byte
    unsigned char n  = chip8->opcode & 0x000F;

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
        switch(chip8->opcode & 0x00FF)
        {
        case 0x9E: // SKP Vx
            printf("0x%04X: SKP V%X\n", chip8->pc, x);
            chip8_skp_vx(chip8, x);
            break;
        case 0xA1: // SKNP Vx
            printf("0x%04X: SKNP V%X\n", chip8->pc, x);
            chip8_sknp_vx(chip8, x);
            break;
        }
        break;
    case 0xF000: // Fx07 - LD Vx, DT
        switch(chip8->opcode & 0x00FF)
        {
        case 0x07: // LD Vx, DT
            printf("0x%04X: LD V%X, DT\n", chip8->pc, x);
            chip8_ld_vx_dt(chip8, x);
            break;
        case 0x0A: // LD Vx, K
            printf("0x%04X: LD V%X, K\n", chip8->pc, x);
            chip8_ld_vx_k(chip8, x);
            break;
        case 0x15: // LD DT, Vx
            printf("0x%04X: LD DT, V%X\n", chip8->pc, x);
            chip8_ld_dt_vx(chip8, x);
            break;
        case 0x18: // LD ST, Vx
            printf("0x%04X: LD ST, V%X\n", chip8->pc, x);
            chip8_ld_st_vx(chip8, x);
            break;
        case 0x1E: // ADD I, Vx
            printf("0x%04X: ADD I, V%X\n", chip8->pc, x);
            chip8_add_i_vx(chip8, x);
            break;
        case 0x29: // LD F, Vx
            printf("0x%04X: LD F, V%X\n", chip8->pc, x);
            chip8_ld_f_vx(chip8, x);
            break;
        case 0x33: // LD B, Vx
            printf("0x%04X: LD B, V%X\n", chip8->pc, x);
            chip8_ld_b_vx(chip8, x);
            break;
        case 0x55: // LD [I], Vx
            printf("0x%04X: LD [I], V%X\n", chip8->pc, x);
            chip8_ld_i_vx(chip8, x);
            break;
        case 0x65: // LD Vx, [I]
            printf("0x%04X: LD V%X, [I]\n", chip8->pc, x);
            chip8_ld_vx_i(chip8, x);
            break;
        }
        break;
    }

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

void chip8_LoadProgram(Chip8* chip8, char* program)
{
    // Load program
    printf("Loading program %s\n", program);
    FILE* filePtr = fopen(program, "rb");
    if(filePtr == NULL)
    {
        printf("Error: Unable to open file %s\n", program);
        exit(1);
    }

    fseek(filePtr, 0, SEEK_END);
    int size = ftell(filePtr);
    rewind(filePtr);

    if(size > 4096 - PROGRAM_RAM)
    {
        printf("Program too big!\n");
        fclose(filePtr);
        exit(1);
    }

    size_t bytesRead = fread(&chip8->memory[PROGRAM_RAM], 1, size, filePtr);
    if(bytesRead != size)
    {
        printf("Failed to read entire file\n");
        fclose(filePtr);
        exit(1);
    }

    fclose(filePtr);
}

void chip8_InitDisplay(Chip8* chip8)
{
    SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("CHIP8", // window title
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH * SCALE_FACTOR,  // width, in pixels
                              SCREEN_HEIGHT * SCALE_FACTOR, // height, in pixels
                              SDL_WINDOW_RESIZABLE);

    // Check that the window was successfully created
    if(window == NULL)
    {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n",
                     SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n",
                     SDL_GetError());
        exit(1);
    }

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    canvas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                               SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(canvas == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create canvas: %s\n",
                     SDL_GetError());
        exit(1);
    }

    SDL_ShowWindow(window);
}


void chip8_RenderLoop(void)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            SDL_DestroyTexture(canvas);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                int w = event.window.data1;
                int h = event.window.data2;
                SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            }
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_z: chip8.key[0x1] = 1; break;
            case SDLK_x: chip8.key[0x2] = 1; break;
            case SDLK_c: chip8.key[0x3] = 1; break;
            case SDLK_v: chip8.key[0xC] = 1; break;
            case SDLK_a: chip8.key[0x4] = 1; break;
            case SDLK_s: chip8.key[0x5] = 1; break;
            case SDLK_d: chip8.key[0x6] = 1; break;
            case SDLK_f: chip8.key[0xD] = 1; break;
            case SDLK_q: chip8.key[0x7] = 1; break;
            case SDLK_w: chip8.key[0x8] = 1; break;
            case SDLK_e: chip8.key[0x9] = 1; break;
            case SDLK_r: chip8.key[0xE] = 1; break;
            case SDLK_1: chip8.key[0x1] = 1; break;
            case SDLK_2: chip8.key[0x2] = 1; break;
            case SDLK_3: chip8.key[0x3] = 1; break;
            case SDLK_4: chip8.key[0xC] = 1; break;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_z: chip8.key[0x1] = 0; break;
            case SDLK_x: chip8.key[0x2] = 0; break;
            case SDLK_c: chip8.key[0x3] = 0; break;
            case SDLK_v: chip8.key[0xC] = 0; break;
            case SDLK_a: chip8.key[0x4] = 0; break;
            case SDLK_s: chip8.key[0x5] = 0; break;
            case SDLK_d: chip8.key[0x6] = 0; break;
            case SDLK_f: chip8.key[0xD] = 0; break;
            case SDLK_q: chip8.key[0x7] = 0; break;
            case SDLK_w: chip8.key[0x8] = 0; break;
            case SDLK_e: chip8.key[0x9] = 0; break;
            case SDLK_r: chip8.key[0xE] = 0; break;
            case SDLK_1: chip8.key[0x1] = 0; break;
            case SDLK_2: chip8.key[0x2] = 0; break;
            case SDLK_3: chip8.key[0x3] = 0; break;
            case SDLK_4: chip8.key[0xC] = 0; break;
            }
        }
    }

    if(chip8.drawFlag)
    {
        uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
        for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        {
            pixels[i] = chip8.gfx[i] ? 0x0000FF00 : 0x00000000;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_UpdateTexture(canvas, NULL, pixels, SCREEN_WIDTH * sizeof(uint32_t));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, canvas, NULL, NULL);
        SDL_RenderPresent(renderer);

        chip8.drawFlag = 0;
    }
}
