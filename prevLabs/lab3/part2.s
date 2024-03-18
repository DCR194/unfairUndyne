.text
/* Program to Count the number of 1’s in a 32-bit word,
located at InputWord */
.global _start

ONES:
	subi sp, sp, 4
	stw r9 , (sp)
	subi sp, sp, 4
	stw r10 , (sp)
	subi sp, sp, 4
	stw r11 , (sp)
	subi sp, sp, 4
	stw r12 , (sp)
	
	movi r9, 0
	movi r10, 32
	mov r11, r4
	movia r12, 0
	
	bitwiseAnd:
	
	subi r10, r10, 1
	
	andi r9, r11, 1
	add r12, r12, r9
	roli r11, r11, 1
	
	bgt r10, r0, bitwiseAnd
	
	mov r2, r12
	
	ldw r12, (sp)
	addi sp, sp, 4
	ldw r11, (sp)
	addi sp, sp, 4
	ldw r10, (sp)
	addi sp, sp, 4
	ldw r9, (sp)
	addi sp, sp, 4
	ret

_start:

	movia sp, 0x200
	movia r8, InputWord
	ldw r4, (r8)
	
	call ONES
	
	stw r2, (r8)
	

endiloop: br endiloop
.data
InputWord: .word 0x4a01fead
Answer: .word 0
