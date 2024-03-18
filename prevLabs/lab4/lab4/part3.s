.global _start
_start:

	movi r14, 0
	movi r15, 255
	movia r9, LEDs
	movia r11, counterLow
	movia r8, 0x7840
	stwio r8, (r11)
	movia r11, counterHigh
	movia r8, 0x17d
	stwio r8, (r11)
	
	movia r11, controlReg
	ldwio r8, (r11)
	ori r8, r8, 0x6
	stwio r8, (r11)
	
	movia r11, statusReg
main:
	
	SUB_LOOP:
	ldwio r8, (r11)
	andi r8, r8, 0x1
	beq r8, r0, SUB_LOOP
	
	bne r14, r15, skipWrap
		movi r14, 0
		stwio r14, (r9)
		subi r8, r8, 1
		stwio r8, (r11)
		br SUB_LOOP
		
	skipWrap:
	
	addi r14, r14, 1
	stwio r14, (r9)
	subi r8, r8, 1
	stwio r8, (r11)
	
	br SUB_LOOP
	
	
	
iloop: br iloop
.equ statusReg, 0xff202000
.equ counterLow, 0xff202008
.equ counterHigh, 0xff20200c
.equ controlReg, 0xff202004
.equ LEDs, 0xff200000