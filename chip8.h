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

#ifndef CHIP8_H
#define CHIP8_H

typedef struct {
    unsigned short opcode; // Current opcode
    unsigned char* memory; // 4K memory [4096]
    unsigned char* V; // 16 8-bit registers [16]
    unsigned short I; // Index register
    unsigned short pc; // Program counter
    unsigned char* gfx; // Graphics buffer [64 * 32]
    unsigned char delay_timer; // Delay timer
    unsigned char sound_timer; // Sound timer
    unsigned short* stack; // Stack [16]
    unsigned short sp; // Stack pointer
    unsigned char* key; // Keypad [16]
    unsigned char drawFlag; // Flag to indicate if screen needs to be redrawn
} Chip8;

#endif

// 0nnn - SYS addr
void chip8_sys(Chip8* chip8, unsigned short nnn);
void chip8_cls(Chip8* chip8);
void chip8_ret(Chip8* chip8);
void chip8_jp(Chip8* chip8, unsigned short nnn);
void chip8_call(Chip8* chip8, unsigned short nnn);
void chip8_se(Chip8* chip8, unsigned char x, unsigned char kk);
void chip8_sne(Chip8* chip8, unsigned char x, unsigned char kk);
void chip8_se_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_ld_vx_byte(Chip8* chip8, unsigned char x, unsigned char kk);
void chip8_add_vx_byte(Chip8* chip8, unsigned char x, unsigned char kk);
void chip8_ld_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_or_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_and_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_xor_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_add_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_sub_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_shr_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_subn_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_shl_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_sne_vx_vy(Chip8* chip8, unsigned char x, unsigned char y);
void chip8_ld_i_addr(Chip8* chip8, unsigned char I, unsigned short nnn);
void chip8_jp_v0_addr(Chip8* chip8, unsigned short nnn);
void chip8_rnd_vx_byte(Chip8* chip8, unsigned char x, unsigned short kk);
void chip8_drw_vx_vy_nibble(Chip8* chip8, unsigned char x, unsigned char y, unsigned char n);
void chip8_skp_vx(Chip8* chip8, unsigned char x);
void chip8_sknp_vx(Chip8* chip8, unsigned char x);
void chip8_ld_vx_dt(Chip8* chip8, unsigned char x);
void chip8_ld_vx_k(Chip8* chip8); // TODO: Implement this
void chip8_ld_dt_vx(Chip8* chip8, unsigned char x);
void chip8_ld_st_vx(Chip8* chip8, unsigned char x);
void chip8_add_i_vx(Chip8* chip8, unsigned char x);
void chip8_ld_f_vx(Chip8* chip8); // TODO: Implement this
void chip8_ld_b_vx(Chip8* chip8); // TODO: Implement this
void chip8_ld_i_vx(Chip8* chip8);
void chip8_ld_vx_i(Chip8* chip8);
