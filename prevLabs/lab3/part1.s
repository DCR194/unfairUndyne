.text
/* Program to Count the number of 1’s in a 32-bit word,
located at InputWord */
.global _start
_start:

	movia r8, InputWord
	movi r9, 0
	movi r10, 32
	ldw r11, (r8)
	movia r12, 0
	
	bitwiseAnd:
	
	subi r10, r10, 1
	
	andi r9, r11, 1
	add r12, r12, r9
	roli r11, r11, 1
	
	bgt r10, r0, bitwiseAnd
	
	movia r8, Answer
	stw r12, (r8)
	

endiloop: br endiloop
.data
InputWord: .word 0x4a01fead
Answer: .word 0

	