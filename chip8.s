	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 4	sdk_version 14, 4
	.globl	_chip8_sys                      ; -- Begin function chip8_sys
	.p2align	2
_chip8_sys:                             ; @chip8_sys
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strh	w1, [sp, #6]
	ldrh	w8, [sp, #6]
	ldr	x9, [sp, #8]
	strh	w8, [x9, #26]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_cls                      ; -- Begin function chip8_cls
	.p2align	2
_chip8_cls:                             ; @chip8_cls
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	str	wzr, [sp, #4]
	b	LBB1_1
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #4]
	subs	w8, w8, #2048
	cset	w8, ge
	tbnz	w8, #0, LBB1_4
	b	LBB1_2
LBB1_2:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #32]
	ldrsw	x9, [sp, #4]
	add	x8, x8, x9
	strb	wzr, [x8]
	b	LBB1_3
LBB1_3:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #4]
	add	w8, w8, #1
	str	w8, [sp, #4]
	b	LBB1_1
LBB1_4:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ret                      ; -- Begin function chip8_ret
	.p2align	2
_chip8_ret:                             ; @chip8_ret
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #48]
	ldr	x9, [sp, #8]
	ldrh	w9, [x9, #56]
                                        ; kill: def $x9 killed $w9
	add	x8, x8, x9, lsl #1
	ldrh	w8, [x8]
	ldr	x9, [sp, #8]
	strh	w8, [x9, #26]
	ldr	x9, [sp, #8]
	ldrh	w10, [x9, #56]
	mov	w8, #-1
	add	w8, w8, w10, uxth
	strh	w8, [x9, #56]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_jp                       ; -- Begin function chip8_jp
	.p2align	2
_chip8_jp:                              ; @chip8_jp
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strh	w1, [sp, #6]
	ldrh	w8, [sp, #6]
	ldr	x9, [sp, #8]
	strh	w8, [x9, #26]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_call                     ; -- Begin function chip8_call
	.p2align	2
_chip8_call:                            ; @chip8_call
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strh	w1, [sp, #6]
	ldr	x9, [sp, #8]
	ldrh	w8, [x9, #56]
	add	w8, w8, #1
	strh	w8, [x9, #56]
	ldr	x8, [sp, #8]
	ldrh	w8, [x8, #26]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #48]
	ldr	x10, [sp, #8]
	ldrh	w10, [x10, #56]
                                        ; kill: def $x10 killed $w10
	add	x9, x9, x10, lsl #1
	strh	w8, [x9]
	ldrh	w8, [sp, #6]
	ldr	x9, [sp, #8]
	strh	w8, [x9, #26]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_se                       ; -- Begin function chip8_se
	.p2align	2
_chip8_se:                              ; @chip8_se
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldrb	w9, [sp, #6]
	subs	w8, w8, w9
	cset	w8, ne
	tbnz	w8, #0, LBB5_2
	b	LBB5_1
LBB5_1:
	ldr	x9, [sp, #8]
	ldrh	w8, [x9, #26]
	add	w8, w8, #2
	strh	w8, [x9, #26]
	b	LBB5_2
LBB5_2:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_sne                      ; -- Begin function chip8_sne
	.p2align	2
_chip8_sne:                             ; @chip8_sne
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldrb	w9, [sp, #6]
	subs	w8, w8, w9
	cset	w8, eq
	tbnz	w8, #0, LBB6_2
	b	LBB6_1
LBB6_1:
	ldr	x9, [sp, #8]
	ldrh	w8, [x9, #26]
	add	w8, w8, #2
	strh	w8, [x9, #26]
	b	LBB6_2
LBB6_2:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_se_vx_vy                 ; -- Begin function chip8_se_vx_vy
	.p2align	2
_chip8_se_vx_vy:                        ; @chip8_se_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #6]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	subs	w8, w8, w9
	cset	w8, ne
	tbnz	w8, #0, LBB7_2
	b	LBB7_1
LBB7_1:
	ldr	x9, [sp, #8]
	ldrh	w8, [x9, #26]
	add	w8, w8, #2
	strh	w8, [x9, #26]
	b	LBB7_2
LBB7_2:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_vx_byte               ; -- Begin function chip8_ld_vx_byte
	.p2align	2
_chip8_ld_vx_byte:                      ; @chip8_ld_vx_byte
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldrb	w8, [sp, #6]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	add	x9, x9, x10
	strb	w8, [x9]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_add_vx_byte              ; -- Begin function chip8_add_vx_byte
	.p2align	2
_chip8_add_vx_byte:                     ; @chip8_add_vx_byte
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldrb	w9, [sp, #6]
	add	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_vx_vy                 ; -- Begin function chip8_ld_vx_vy
	.p2align	2
_chip8_ld_vx_vy:                        ; @chip8_ld_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #6]
                                        ; kill: def $x9 killed $w9
	add	x8, x8, x9
	ldrb	w8, [x8]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	add	x9, x9, x10
	strb	w8, [x9]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_or_vx_vy                 ; -- Begin function chip8_or_vx_vy
	.p2align	2
_chip8_or_vx_vy:                        ; @chip8_or_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #6]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	orr	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_and_vx_vy                ; -- Begin function chip8_and_vx_vy
	.p2align	2
_chip8_and_vx_vy:                       ; @chip8_and_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #6]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	and	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_xor_vx_vy                ; -- Begin function chip8_xor_vx_vy
	.p2align	2
_chip8_xor_vx_vy:                       ; @chip8_xor_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #6]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	eor	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_add_vx_vy                ; -- Begin function chip8_add_vx_vy
	.p2align	2
_chip8_add_vx_vy:                       ; @chip8_add_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldrb	w8, [sp, #7]
	ldrb	w9, [sp, #6]
	add	w8, w8, w9
	strh	w8, [sp, #4]
	ldrsh	w8, [sp, #4]
	subs	w8, w8, #255
	cset	w8, le
	tbnz	w8, #0, LBB14_2
	b	LBB14_1
LBB14_1:
	ldr	x8, [sp, #8]
	ldr	x9, [x8, #16]
	mov	w8, #1
	strb	w8, [x9, #15]
	b	LBB14_3
LBB14_2:
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	strb	wzr, [x8, #15]
	b	LBB14_3
LBB14_3:
	ldrh	w8, [sp, #4]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	add	x9, x9, x10
	strb	w8, [x9]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_sub_vx_vy                ; -- Begin function chip8_sub_vx_vy
	.p2align	2
_chip8_sub_vx_vy:                       ; @chip8_sub_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #6]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	subs	w8, w8, w9
	cset	w8, le
	tbnz	w8, #0, LBB15_2
	b	LBB15_1
LBB15_1:
	ldr	x8, [sp, #8]
	ldr	x9, [x8, #16]
	mov	w8, #1
	strb	w8, [x9, #15]
	b	LBB15_3
LBB15_2:
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	strb	wzr, [x8, #15]
	b	LBB15_3
LBB15_3:
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #6]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	subs	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_shr_vx_vy                ; -- Begin function chip8_shr_vx_vy
	.p2align	2
_chip8_shr_vx_vy:                       ; @chip8_shr_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	and	w8, w8, #0x1
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	strb	w8, [x9, #15]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	mov	w9, #2
	sdiv	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_subn_vx_vy               ; -- Begin function chip8_subn_vx_vy
	.p2align	2
_chip8_subn_vx_vy:                      ; @chip8_subn_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #6]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	subs	w8, w8, w9
	cset	w8, le
	tbnz	w8, #0, LBB17_2
	b	LBB17_1
LBB17_1:
	ldr	x8, [sp, #8]
	ldr	x9, [x8, #16]
	mov	w8, #1
	strb	w8, [x9, #15]
	b	LBB17_3
LBB17_2:
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	strb	wzr, [x8, #15]
	b	LBB17_3
LBB17_3:
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #6]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	subs	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_shl_vx_vy                ; -- Begin function chip8_shl_vx_vy
	.p2align	2
_chip8_shl_vx_vy:                       ; @chip8_shl_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	and	w8, w8, #0x1
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	strb	w8, [x9, #15]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	lsl	w8, w8, #1
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_sne_vx_vy                ; -- Begin function chip8_sne_vx_vy
	.p2align	2
_chip8_sne_vx_vy:                       ; @chip8_sne_vx_vy
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #6]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	subs	w8, w8, w9
	cset	w8, eq
	tbnz	w8, #0, LBB19_2
	b	LBB19_1
LBB19_1:
	ldr	x9, [sp, #8]
	ldrh	w8, [x9, #26]
	add	w8, w8, #2
	strh	w8, [x9, #26]
	b	LBB19_2
LBB19_2:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_i_addr                ; -- Begin function chip8_ld_i_addr
	.p2align	2
_chip8_ld_i_addr:                       ; @chip8_ld_i_addr
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strh	w2, [sp, #4]
	ldrh	w8, [sp, #4]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	add	x9, x9, x10
	strb	w8, [x9]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_jp_v0_addr               ; -- Begin function chip8_jp_v0_addr
	.p2align	2
_chip8_jp_v0_addr:                      ; @chip8_jp_v0_addr
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strh	w1, [sp, #6]
	ldrh	w8, [sp, #6]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w9, [x9]
	add	w8, w8, w9
	ldr	x9, [sp, #8]
	strh	w8, [x9, #26]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_rnd_vx_byte              ; -- Begin function chip8_rnd_vx_byte
	.p2align	2
_chip8_rnd_vx_byte:                     ; @chip8_rnd_vx_byte
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strh	w2, [sp, #4]
	bl	_rand
	mov	w9, #255
	sdiv	w8, w0, w9
	mul	w8, w8, w9
	subs	w8, w0, w8
	str	w8, [sp]
	ldr	w8, [sp]
	ldrh	w9, [sp, #4]
	and	w8, w8, w9
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	strb	w8, [x9, x10]
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_drw_vx_vy_nibble         ; -- Begin function chip8_drw_vx_vy_nibble
	.p2align	2
_chip8_drw_vx_vy_nibble:                ; @chip8_drw_vx_vy_nibble
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	strb	w2, [sp, #6]
	strb	w3, [sp, #5]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_skp_vx                   ; -- Begin function chip8_skp_vx
	.p2align	2
_chip8_skp_vx:                          ; @chip8_skp_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #64]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	subs	w8, w8, #1
	cset	w8, ne
	tbnz	w8, #0, LBB24_2
	b	LBB24_1
LBB24_1:
	ldr	x9, [sp, #8]
	ldrh	w8, [x9, #26]
	add	w8, w8, #2
	strh	w8, [x9, #26]
	b	LBB24_2
LBB24_2:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_sknp_vx                  ; -- Begin function chip8_sknp_vx
	.p2align	2
_chip8_sknp_vx:                         ; @chip8_sknp_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #64]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
                                        ; kill: def $x9 killed $w9
	ldrb	w8, [x8, x9]
	subs	w8, w8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB25_2
	b	LBB25_1
LBB25_1:
	ldr	x9, [sp, #8]
	ldrh	w8, [x9, #26]
	add	w8, w8, #2
	strh	w8, [x9, #26]
	b	LBB25_2
LBB25_2:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_vx_dt                 ; -- Begin function chip8_ld_vx_dt
	.p2align	2
_chip8_ld_vx_dt:                        ; @chip8_ld_vx_dt
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	ldr	x8, [sp, #8]
	ldrb	w8, [x8, #40]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	add	x9, x9, x10
	strb	w8, [x9]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_vx_k                  ; -- Begin function chip8_ld_vx_k
	.p2align	2
_chip8_ld_vx_k:                         ; @chip8_ld_vx_k
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_dt_vx                 ; -- Begin function chip8_ld_dt_vx
	.p2align	2
_chip8_ld_dt_vx:                        ; @chip8_ld_dt_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	add	x8, x8, x9
	ldrb	w8, [x8]
	ldr	x9, [sp, #8]
	strb	w8, [x9, #40]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_st_vx                 ; -- Begin function chip8_ld_st_vx
	.p2align	2
_chip8_ld_st_vx:                        ; @chip8_ld_st_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrb	w9, [sp, #7]
                                        ; kill: def $x9 killed $w9
	add	x8, x8, x9
	ldrb	w8, [x8]
	ldr	x9, [sp, #8]
	strb	w8, [x9, #41]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_add_i_vx                 ; -- Begin function chip8_add_i_vx
	.p2align	2
_chip8_add_i_vx:                        ; @chip8_add_i_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	strb	w1, [sp, #7]
	ldr	x8, [sp, #8]
	ldrh	w8, [x8, #24]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrb	w10, [sp, #7]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	add	w8, w8, w9
	ldr	x9, [sp, #8]
	strh	w8, [x9, #24]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_f_vx                  ; -- Begin function chip8_ld_f_vx
	.p2align	2
_chip8_ld_f_vx:                         ; @chip8_ld_f_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_b_vx                  ; -- Begin function chip8_ld_b_vx
	.p2align	2
_chip8_ld_b_vx:                         ; @chip8_ld_b_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_i_vx                  ; -- Begin function chip8_ld_i_vx
	.p2align	2
_chip8_ld_i_vx:                         ; @chip8_ld_i_vx
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	str	wzr, [sp, #4]
	b	LBB33_1
LBB33_1:                                ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #4]
	subs	w8, w8, #15
	cset	w8, ge
	tbnz	w8, #0, LBB33_4
	b	LBB33_2
LBB33_2:                                ;   in Loop: Header=BB33_1 Depth=1
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #16]
	ldrsw	x9, [sp, #4]
	add	x8, x8, x9
	ldrb	w8, [x8]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #8]
	ldr	x10, [sp, #8]
	ldrh	w10, [x10, #24]
	ldr	w11, [sp, #4]
	add	w10, w10, w11
	add	x9, x9, w10, sxtw
	strb	w8, [x9]
	b	LBB33_3
LBB33_3:                                ;   in Loop: Header=BB33_1 Depth=1
	ldr	w8, [sp, #4]
	add	w8, w8, #1
	str	w8, [sp, #4]
	b	LBB33_1
LBB33_4:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_chip8_ld_vx_i                  ; -- Begin function chip8_ld_vx_i
	.p2align	2
_chip8_ld_vx_i:                         ; @chip8_ld_vx_i
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	str	wzr, [sp, #4]
	b	LBB34_1
LBB34_1:                                ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #4]
	subs	w8, w8, #15
	cset	w8, ge
	tbnz	w8, #0, LBB34_4
	b	LBB34_2
LBB34_2:                                ;   in Loop: Header=BB34_1 Depth=1
	ldr	x8, [sp, #8]
	ldr	x8, [x8, #8]
	ldr	x9, [sp, #8]
	ldrh	w9, [x9, #24]
	ldr	w10, [sp, #4]
	add	w9, w9, w10
	add	x8, x8, w9, sxtw
	ldrb	w8, [x8]
	ldr	x9, [sp, #8]
	ldr	x9, [x9, #16]
	ldrsw	x10, [sp, #4]
	add	x9, x9, x10
	strb	w8, [x9]
	b	LBB34_3
LBB34_3:                                ;   in Loop: Header=BB34_1 Depth=1
	ldr	w8, [sp, #4]
	add	w8, w8, #1
	str	w8, [sp, #4]
	b	LBB34_1
LBB34_4:
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__const
	.globl	_SCREEN_WIDTH                   ; @SCREEN_WIDTH
	.p2align	2, 0x0
_SCREEN_WIDTH:
	.long	64                              ; 0x40

	.globl	_SCREEN_HEIGHT                  ; @SCREEN_HEIGHT
	.p2align	2, 0x0
_SCREEN_HEIGHT:
	.long	32                              ; 0x20

	.globl	_SCREEN_SIZE                    ; @SCREEN_SIZE
	.p2align	2, 0x0
_SCREEN_SIZE:
	.long	2048                            ; 0x800

	.section	__DATA,__data
	.globl	_chip8_fontset                  ; @chip8_fontset
_chip8_fontset:
	.ascii	"\360\220\220\220\360 `  p\360\020\360\200\360\360\020\360\020\360\220\220\360\020\020\360\200\360\020\360\360\200\360\220\360\360\020 @@\360\220\360\220\360\360\220\360\020\360\360\220\360\220\220\340\220\340\220\340\360\200\200\200\360\340\220\220\220\340\360\200\360\200\360\360\200\360\200\200"

.subsections_via_symbols
