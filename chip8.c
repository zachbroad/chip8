#include "chip8.h"
#include "constants.h"
#include <stdlib.h>

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

// 0nnn - SYS addr
void chip8_sys(Chip8* chip8, unsigned short nnn)
{
    chip8->pc = nnn; // TODO : ignore?
}

// 00E0 - CLS
void chip8_cls(Chip8* chip8)
{
    for (int i = 0; i < SCREEN_SIZE; i++) // 64x32 Screen
    {
        chip8->gfx[i] = 0; // Set to black
    }
}

// 00EE - RET
void chip8_ret(Chip8* chip8)
{
    chip8->pc = chip8->stack[chip8->sp];
    chip8->sp--;
}

// 1nnn - JP addr
// Jump to a machine code routine at nnn.
void chip8_jp(Chip8* chip8, unsigned short nnn)
{
    chip8->pc = nnn;
}

// 2nnn - CALL addr
// Clear the display
void chip8_call(Chip8* chip8, unsigned short nnn)
{
    chip8->sp++;
    chip8->stack[chip8->sp] = chip8->pc;
    chip8->pc = nnn;
}

// 3xkk - SE Vx, byte
void chip8_se(Chip8* chip8, unsigned char x, unsigned char kk)
{
    if (chip8->V[x] == kk)
    {
        chip8->pc += 2;
    }
}

// 4xkk - SNE Vx, byte
void chip8_sne(Chip8* chip8, unsigned char x, unsigned char kk)
{
    if (chip8->V[x] != kk)
    {
        chip8->pc += 2;
    }
}

// 5xy0 - SE Vx, Vy
void chip8_se_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    if (chip8->V[x] == chip8->V[y])
    {
        chip8->pc += 2;
    }
}

// 6xkk - LD Vx, byte
void chip8_ld_vx_byte(Chip8* chip8, unsigned char x, unsigned char kk)
{
    chip8->V[x] = kk;
}

// 7xkk - ADD Vx, byte
void chip8_add_vx_byte(Chip8* chip8, unsigned char x, unsigned char kk)
{
    chip8->V[x] = chip8->V[x] + kk;
}

// 8xy0 - LD Vx, Vy
void chip8_ld_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    chip8->V[x] = chip8->V[y];
}

// 8xy1 - OR Vx, Vy
void chip8_or_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    chip8->V[x] = chip8->V[x] | chip8->V[y];
}

// 8xy2 - AND Vx, Vy
void chip8_and_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    chip8->V[x] = chip8->V[x] & chip8->V[y];
}

// 8xy3 - XOR Vx, Vy
void chip8_xor_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    chip8->V[x] = chip8->V[x] ^ chip8->V[y];
}

// 8xy4 - ADD Vx, Vy
void chip8_add_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    short temp = x + y;
    if (temp > 255) 
    {
        chip8->V[0xF] = 1;
    }
    else
    {
        chip8->V[0xF] = 0;
    }

    chip8->V[x] = (unsigned char) temp;
}

// 8xy5 - SUB Vx, Vy
// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
void chip8_sub_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    if (chip8->V[x] > chip8->V[y])
    {
        chip8->V[0xF] = 1;
    }
    else 
    {
        chip8->V[0xF] = 0;
    }

    chip8->V[x] = chip8->V[x] - chip8->V[y];
}

// 8xy6 - SHR Vx {, Vy}
// Set Vx = Vx SHR 1.
// If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
void chip8_shr_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    chip8->V[0xF] = chip8->V[x] & 0x1;
    chip8->V[x] = chip8->V[x] / 2;
}


// 8xy7 - SUBN Vx, Vy
// Set Vx = Vy - Vx, set VF = NOT borrow.
// If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
void chip8_subn_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    if (chip8->V[y] > chip8->V[x])
    {
        chip8->V[0xF] = 1;
    }
    else
    {
        chip8->V[0xF] = 0;
    }

    chip8->V[x] = chip8->V[y] - chip8->V[x];
}


// 8xyE - SHL Vx {, Vy}
// Set Vx = Vx SHL 1.
// If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
void chip8_shl_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    chip8->V[0xF] = chip8->V[x] & 0x1;
    chip8->V[x] = chip8->V[x] * 2;
}

// 9xy0 - SNE Vx, Vy
void chip8_sne_vx_vy(Chip8* chip8, unsigned char x, unsigned char y)
{
    if (chip8->V[x] != chip8->V[y])
    {
        chip8->pc += 2;
    }
}

// Annn - LD I, addr
void chip8_ld_i_addr(Chip8* chip8, unsigned char I, unsigned short nnn)
{
    chip8->V[I] = nnn;
}

// Bnnn - JP V0, addr
// Jump to location nnn + V0.
// The program counter is set to nnn plus the value of V0.
void chip8_jp_v0_addr(Chip8* chip8, unsigned short nnn)
{
    chip8->pc = nnn + chip8->V[0];
}

// Cxkk - RND Vx, byte
// Set Vx = random byte AND kk.
// The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
void chip8_rnd_vx_byte(Chip8* chip8, unsigned char x, unsigned short kk)
{
    int rn = rand() % 255;
    chip8->V[x] = rn & (unsigned short) kk;
}

// Dxyn - DRW Vx, Vy, nibble
// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
// The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
void chip8_drw_vx_vy_nibble(Chip8* chip8, unsigned char x, unsigned char y, unsigned char n)
{
}

// Ex9E - SKP Vx
// Skip next instruction if key with the value of Vx is pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
void chip8_skp_vx(Chip8* chip8, unsigned char x)
{
    // TODO: Check
    if (chip8->key[chip8->V[x]] == 1)
    {
        chip8->pc += 2;
    }
}
 
// ExA1 - SKNP Vx
// Skip next instruction if key with the value of Vx is not pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
void chip8_sknp_vx(Chip8* chip8, unsigned char x)
{
    // TODO:
    if (chip8->key[chip8->V[x]] == 0)
    {
        chip8->pc += 2;
    }
}

// Fx07 - LD Vx, DT
void chip8_ld_vx_dt(Chip8* chip8, unsigned char x)
{
    chip8->V[x] = chip8->delay_timer;
}

// Fx0A - LD Vx, K
void chip8_ld_vx_k(Chip8* chip8)
{
    // TODO: Implement
}

// Fx15 - LD DT, Vx
// Load Delay Timer from register X
void chip8_ld_dt_vx(Chip8* chip8, unsigned char x)
{
    chip8->delay_timer = chip8->V[x];
}

// Fx18 - LD ST, Vx
// Load sound timer from register x
void chip8_ld_st_vx(Chip8* chip8, unsigned char x)
{
    chip8->sound_timer = chip8->V[x];
}

// Fx1E - ADD I, Vx
void chip8_add_i_vx(Chip8* chip8, unsigned char x)
{
    chip8->I = chip8->I + chip8->V[x];
}

// Fx29 - LD F, Vx
void chip8_ld_f_vx(Chip8* chip8)
{
    // TODO: Implement
}

// Fx33 - LD B, Vx
void chip8_ld_b_vx(Chip8* chip8)
{

}

// Fx55 - LD [I], Vx
void chip8_ld_i_vx(Chip8* chip8)
{
    for(int i = 0; i < 0xF; i++)
    {
        chip8->memory[chip8->I + i] = chip8->V[i]; // todo: confirm
    }
}

// Fx65 - LD Vx, [I]
void chip8_ld_vx_i(Chip8* chip8)
{
    for(int i = 0; i < 0xF; i++)
    {
        chip8->V[i] = chip8->memory[chip8->I + i]; // todo: confirm
    }
}


// TODO: Super Chip-48 Instructions
