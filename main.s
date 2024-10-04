	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 14, 4	sdk_version 14, 4
	.globl	_getAddr                        ; -- Begin function getAddr
	.p2align	2
_getAddr:                               ; @getAddr
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	strh	w0, [sp, #14]
	ldrh	w8, [sp, #14]
	and	w8, w8, #0xfff
	and	w0, w8, #0xffff
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	stp	x28, x27, [sp, #-32]!           ; 16-byte Folded Spill
	.cfi_def_cfa_offset 32
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w27, -24
	.cfi_offset w28, -32
	sub	sp, sp, #3712
	sub	x8, x29, #112
	str	x8, [sp, #16]                   ; 8-byte Folded Spill
	stur	wzr, [x29, #-20]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	mov	x0, #4096
	bl	_malloc
	ldr	x8, [sp, #16]                   ; 8-byte Folded Reload
	str	x0, [x8, #16]
	mov	x0, #16
	str	x0, [sp, #8]                    ; 8-byte Folded Spill
	bl	_malloc
	ldr	x9, [sp, #16]                   ; 8-byte Folded Reload
	mov	x8, x0
	ldr	x0, [sp, #8]                    ; 8-byte Folded Reload
	str	x8, [x9, #24]
	bl	_malloc
	ldr	x9, [sp, #16]                   ; 8-byte Folded Reload
	mov	x8, x0
	ldr	x0, [sp, #8]                    ; 8-byte Folded Reload
	str	x8, [x9, #56]
	bl	_malloc
	ldr	x8, [sp, #16]                   ; 8-byte Folded Reload
	str	x0, [x8, #72]
	mov	x0, #2048
	bl	_malloc
	ldr	x8, [sp, #16]                   ; 8-byte Folded Reload
	str	x0, [x8, #40]
	sturh	wzr, [x29, #-78]
	sturh	wzr, [x29, #-80]
	sturh	wzr, [x29, #-48]
	sturb	wzr, [x29, #-64]
	sturb	wzr, [x29, #-63]
	sturh	wzr, [x29, #-104]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	adrp	x0, l_.str.3@PAGE
	add	x0, x0, l_.str.3@PAGEOFF
	adrp	x1, l_.str.4@PAGE
	add	x1, x1, l_.str.4@PAGEOFF
	bl	_fopen
	ldr	x8, [sp, #16]                   ; 8-byte Folded Reload
	str	x0, [x8]
	ldr	x2, [x8]
	add	x0, sp, #32
	mov	w1, #3584
	bl	_fgets
	str	wzr, [sp, #28]
	b	LBB1_1
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #28]
	subs	w8, w8, #3584
	cset	w8, ge
	tbnz	w8, #0, LBB1_4
	b	LBB1_2
LBB1_2:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	x9, [sp, #16]                   ; 8-byte Folded Reload
	ldrsw	x10, [sp, #28]
	add	x8, sp, #32
	add	x8, x8, x10
	ldrb	w8, [x8]
	ldr	x9, [x9, #16]
	ldr	w10, [sp, #28]
	add	w10, w10, #512
	add	x9, x9, w10, sxtw
	strb	w8, [x9]
	b	LBB1_3
LBB1_3:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #28]
	add	w8, w8, #1
	str	w8, [sp, #28]
	b	LBB1_1
LBB1_4:
	mov	w8, #512
	sturh	w8, [x29, #-78]
	ldurh	w10, [x29, #-78]
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9]
	adrp	x0, l_.str.5@PAGE
	add	x0, x0, l_.str.5@PAGEOFF
	bl	_printf
	b	LBB1_5
LBB1_5:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x8, [sp, #16]                   ; 8-byte Folded Reload
	sub	x0, x29, #104
	ldr	x9, [x8, #16]
	ldurh	w10, [x29, #-78]
                                        ; kill: def $x10 killed $w10
	ldrb	w9, [x9, x10]
	ldr	x8, [x8, #16]
	ldurh	w10, [x29, #-78]
	add	w10, w10, #1
	ldrb	w8, [x8, w10, sxtw]
	orr	w8, w8, w9, lsl #8
	sturh	w8, [x29, #-104]
	bl	_execute
	ldurh	w8, [x29, #-78]
	add	w8, w8, #2
	sturh	w8, [x29, #-78]
	b	LBB1_5
	.cfi_endproc
                                        ; -- End function
	.globl	_execute                        ; -- Begin function execute
	.p2align	2
_execute:                               ; @execute
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	.cfi_def_cfa_offset 64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	ldur	x8, [x29, #-8]
	ldrh	w11, [x8, #26]
	ldur	x8, [x29, #-8]
	ldrh	w10, [x8]
	mov	x9, sp
                                        ; implicit-def: $x8
	mov	x8, x11
	str	x8, [x9]
                                        ; implicit-def: $x8
	mov	x8, x10
	str	x8, [x9, #8]
	adrp	x0, l_.str.6@PAGE
	add	x0, x0, l_.str.6@PAGEOFF
	bl	_printf
	ldur	x8, [x29, #-8]
	ldrh	w8, [x8]
	and	w9, w8, #0xf000
	stur	w9, [x29, #-12]                 ; 4-byte Folded Spill
	ands	w8, w8, #0xf000
	cset	w8, eq
	tbnz	w8, #0, LBB2_2
	b	LBB2_1
LBB2_1:
	ldur	w8, [x29, #-12]                 ; 4-byte Folded Reload
	subs	w8, w8, #1, lsl #12             ; =4096
	cset	w8, eq
	tbnz	w8, #0, LBB2_8
	b	LBB2_9
LBB2_2:
	ldur	x8, [x29, #-8]
	ldrb	w8, [x8]
	stur	w8, [x29, #-16]                 ; 4-byte Folded Spill
	subs	w8, w8, #224
	cset	w8, eq
	tbnz	w8, #0, LBB2_4
	b	LBB2_3
LBB2_3:
	ldur	w8, [x29, #-16]                 ; 4-byte Folded Reload
	subs	w8, w8, #238
	cset	w8, eq
	tbnz	w8, #0, LBB2_5
	b	LBB2_6
LBB2_4:
	ldur	x0, [x29, #-8]
	bl	_chip8_cls
	b	LBB2_5
LBB2_5:
	ldur	x0, [x29, #-8]
	bl	_chip8_ret
	b	LBB2_6
LBB2_6:
	ldur	x8, [x29, #-8]
	str	x8, [sp, #24]                   ; 8-byte Folded Spill
	ldur	x8, [x29, #-8]
	ldrh	w0, [x8]
	bl	_getAddr
	mov	x8, x0
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	and	w1, w8, #0xffff
	bl	_chip8_sys
	b	LBB2_7
LBB2_7:
	b	LBB2_8
LBB2_8:
	ldur	x8, [x29, #-8]
	str	x8, [sp, #16]                   ; 8-byte Folded Spill
	ldur	x8, [x29, #-8]
	ldrh	w0, [x8]
	bl	_getAddr
	mov	x8, x0
	ldr	x0, [sp, #16]                   ; 8-byte Folded Reload
	and	w1, w8, #0xffff
	bl	_chip8_jp
	b	LBB2_9
LBB2_9:
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__const
	.globl	_PROGRAM_RAM                    ; @PROGRAM_RAM
	.p2align	1, 0x0
_PROGRAM_RAM:
	.short	512                             ; 0x200

	.globl	_INTERPRETER_RAM                ; @INTERPRETER_RAM
	.p2align	1, 0x0
_INTERPRETER_RAM:
	.short	0                               ; 0x0

	.globl	_DISPLAY_RAM                    ; @DISPLAY_RAM
	.p2align	1, 0x0
_DISPLAY_RAM:
	.short	3840                            ; 0xf00

	.section	__DATA,__data
	.globl	_instructions                   ; @instructions
	.p2align	2, 0x0
_instructions:
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	0                               ; 0x0
	.long	19088743                        ; 0x1234567

	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"Starting emulator...\n"

l_.str.1:                               ; @.str.1
	.asciz	"Initializing Chip8...\n"

l_.str.2:                               ; @.str.2
	.asciz	"Loading program...\n"

l_.str.3:                               ; @.str.3
	.asciz	"particle.ch8"

l_.str.4:                               ; @.str.4
	.asciz	"rb"

l_.str.5:                               ; @.str.5
	.asciz	"PC: %d\n"

l_.str.6:                               ; @.str.6
	.asciz	"%d - %d\n"

.subsections_via_symbols
