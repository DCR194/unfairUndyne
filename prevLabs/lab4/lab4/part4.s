.global _start
_start:

	mov r13, r0
	mov r14, r0
	movi r15, 99
	movia r9, LEDs
	movia r10, edgeReg
	movia r11, counterLow
	movia r8, 0x4240
	stwio r8, (r11)
	movia r11, counterHigh
	movia r8, 0xf
	stwio r8, (r11)
	
	movia r11, controlReg
	ldwio r8, (r11)
	ori r8, r8, 0x6
	stwio r8, (r11)
	
	movia r11, statusReg
main:
	
	SUB_LOOP:
	ldwio r12, (r10)
	andi r12, r12, 0xf
	beq r12, r0, pause
		stwio r12, (r10)
		bne r13, r0, skipCheck
		movi r13, 1
		
	pause:
	bne r13, r0, SUB_LOOP
	skipCheck:
	mov r13, r0
	ldwio r8, (r11)
	andi r8, r8, 0x1
	beq r8, r0, SUB_LOOP
	
	bne r14, r15, skipWrap
		andi r14, r14, 896
		addi r14, r14, 128
		addi r15, r15, 128
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
.equ edgeReg, 0xFF20005C