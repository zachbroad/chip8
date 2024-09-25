#include "constants.h"
#include "chip8.h"


void chip8_cls(Chip8* chip8);
void chip8_ret(Chip8* chip8);
void chip8_sys(Chip8* chip8, unsigned short nnn);
void chip8_jp(Chip8* chip8, unsigned short nnn);
void chip8_call(Chip8* chip8, unsigned short nnn);
void chip8_se(Chip8* chip8);
void chip8_sne(Chip8* chip8);
void chip8_se_vx_vy(Chip8* chip8);
void chip8_ld_vx_byte(Chip8* chip8);
void chip8_add_vx_byte(Chip8* chip8);
void chip8_ld_vx_vy(Chip8* chip8);
void chip8_or_vx_vy(Chip8* chip8);
void chip8_and_vx_vy(Chip8* chip8);
void chip8_xor_vx_vy(Chip8* chip8);
void chip8_add_vx_vy(Chip8* chip8);
void chip8_sne_vx_vy(Chip8* chip8);
void chip8_ld_i_addr(Chip8* chip8);
void chip8_ld_vx_dt(Chip8* chip8);
void chip8_ld_vx_k(Chip8* chip8);
void chip8_ld_dt_vx(Chip8* chip8);
void chip8_ld_st_vx(Chip8* chip8);
void chip8_add_i_vx(Chip8* chip8);
void chip8_ld_f_vx(Chip8* chip8);
void chip8_ld_b_vx(Chip8* chip8);
void chip8_ld_i_vx(Chip8* chip8);
void chip8_ld_vx_i(Chip8* chip8);
