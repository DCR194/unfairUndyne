reset:
	ldwio r12, (r10) #edgeReg
	andi r13, r12, 0xf
	beq r13, r0, skipReset
		stwio r13, (r10)
		mov r14, r0
		stwio r14, (r9)
	skipReset:
	ret
	


.global _start
_start:

	movi r14, 0
	movi r15, 255
	movia r9, LEDs
	movia r10, edgeReg
	
main:
	
	DO_DELAY: movia r8, COUNTER_DELAY
	SUB_LOOP: subi r8, r8, 1
	call reset
	bne r8, r0, SUB_LOOP
	
	
	bne r14, r15, skipWrap
		movi r14, 0
		stwio r14, (r9)
		br main
	skipWrap:
	
	addi r14, r14, 1
	stwio r14, (r9)
	br main
	
	
	
iloop: br iloop
.equ COUNTER_DELAY, 0x7a120
.equ LEDs, 0xff200000
.equ edgeReg, 0xFF20005C