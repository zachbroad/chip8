#include "constants.h"
#include "chip8.h"

/**
 * http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
 *
 * 3.1 - Standard Chip-8 Instructions
            00E0 - CLS
            00EE - RET
            0nnn - SYS addr
            1nnn - JP addr
            2nnn - CALL addr
            3xkk - SE Vx, byte
            4xkk - SNE Vx, byte
            5xy0 - SE Vx, Vy
            6xkk - LD Vx, byte
            7xkk - ADD Vx, byte
            8xy0 - LD Vx, Vy
            8xy1 - OR Vx, Vy
            8xy2 - AND Vx, Vy
            8xy3 - XOR Vx, Vy
            8xy4 - ADD Vx, Vy
            8xy5 - SUB Vx, Vy
            8xy6 - SHR Vx {, Vy}
            8xy7 - SUBN Vx, Vy
            8xyE - SHL Vx {, Vy}
            9xy0 - SNE Vx, Vy
            Annn - LD I, addr
            Bnnn - JP V0, addr
            Cxkk - RND Vx, byte
            Dxyn - DRW Vx, Vy, nibble
            Ex9E - SKP Vx
            ExA1 - SKNP Vx
            Fx07 - LD Vx, DT
            Fx0A - LD Vx, K
            Fx15 - LD DT, Vx
            Fx18 - LD ST, Vx
            Fx1E - ADD I, Vx
            Fx29 - LD F, Vx
            Fx33 - LD B, Vx
            Fx55 - LD [I], Vx
            Fx65 - LD Vx, [I]
 */

// 00E0 - CLS
void chip8_cls(Chip8* chip8)
{
    for (int i = 0; i < SCREEN_SIZE; i++) // 64x32 Screen
    {
        gfx[i] = 0; // Set to black
    }
}

// 00EE - RET
void chip8_ret(Chip8* chip8)
{
    // 
}

// 0nnn - SYS addr
void chip8_sys(Chip8* chip8, unsigned short nnn)
{
    chip8->pc = nnn; // TODO : ignore?
}

// 1nnn - JP addr
void chip8_jp(Chip8* chip8, unsigned short nnn)
{
    chip8->pc = nnn;
}

// 2nnn - CALL addr
void chip8_call(Chip8* chip8, unsigned short nnn)
{
    chip8->sp++;
    chip8->stack[chip8->sp] = chip8->pc;
    chip8->pc = nnn;
}

// 3xkk - SE Vx, byte
void chip8_se(Chip8* chip8)
{
}

// 4xkk - SNE Vx, byte
void chip8_sne(Chip8* chip8)
{
}

// 5xy0 - SE Vx, Vy
void chip8_se_vx_vy(Chip8* chip8)
{
}

// 6xkk - LD Vx, byte
void chip8_ld_vx_byte(Chip8* chip8)
{
}

// 7xkk - ADD Vx, byte
void chip8_add_vx_byte(Chip8* chip8)
{
}

// 8xy0 - LD Vx, Vy
void chip8_ld_vx_vy(Chip8* chip8)
{
}

// 8xy1 - OR Vx, Vy
void chip8_or_vx_vy(Chip8* chip8)
{
}

// 8xy2 - AND Vx, Vy
void chip8_and_vx_vy(Chip8* chip8)
{
}

// 8xy3 - XOR Vx, Vy
void chip8_xor_vx_vy(Chip8* chip8)
{
}

// 8xy4 - ADD Vx, Vy
void chip8_add_vx_vy(Chip8* chip8)
{
}

// 9xy0 - SNE Vx, Vy
void chip8_sne_vx_vy(Chip8* chip8)
{
}

// Annn - LD I, addr
void chip8_ld_i_addr(Chip8* chip8)
{
}

// Fx07 - LD Vx, DT
void chip8_ld_vx_dt(Chip8* chip8)
{
}

// Fx0A - LD Vx, K
void chip8_ld_vx_k(Chip8* chip8)
{
}

// Fx15 - LD DT, Vx
void chip8_ld_dt_vx(Chip8* chip8)
{
}

// Fx18 - LD ST, Vx
void chip8_ld_st_vx(Chip8* chip8)
{
}

// Fx1E - ADD I, Vx
void chip8_add_i_vx(Chip8* chip8)
{
}

// Fx29 - LD F, Vx
void chip8_ld_f_vx(Chip8* chip8)
{
}

// Fx33 - LD B, Vx
void chip8_ld_b_vx(Chip8* chip8)
{
}

// Fx55 - LD [I], Vx
void chip8_ld_i_vx(Chip8* chip8)
{
}

// Fx65 - LD Vx, [I]
void chip8_ld_vx_i(Chip8* chip8)
{
}
