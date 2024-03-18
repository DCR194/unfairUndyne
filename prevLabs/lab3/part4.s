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
	
delaytimer: 
	subi sp, sp, 4
	stw r9 , (sp)
	
	movi r9, 32767
	timerLoop:
		beq r9, r0, timerRet
		subi r9, r9, 1
		br timerLoop
	timerRet:
		
		ldw r9 , (sp)
		addi sp, sp, 4

	    ret


.text
/* Program to Count the number of 1’s and Zeroes in a sequence of 32-bit words,
and determines the largest of each */
.global _start
_start:

	movia sp, 0x400
	movia r8, TEST_NUM
	ldw r4, (r8)
	movi r10, 0 #for Zeroes
	movi r11, 0 #for ONes
	subi r7, r0, 1
	
	loopit:
		ldw r4, (r8)
		beq r4, r0, finish
		
		compareones:
			call ONES
			bgt r2, r11, moreones
		
		comparezeros:
			xor r4, r4, r7 # flip the digits from 1 to 0 and 0 to 1
			call ONES
			bgt r2, r10, morezeros
		
		addmore:
		addi r8, r8, 4
		br loopit
		
	moreones: # change the num of highest num of ones
		mov r11, r2
		br comparezeros
		
	morezeros: # change the number of highest num of zeros
		mov r10, r2
		br addmore
	
	
		
	finish:
	movia r15, LargestOnes
	stw r11, (r15)
	movia r15, LargestZeroes
	stw r10, (r15)
	
	mov r22, r10
	.equ LEDs, 0xff200000
	movia r23, LEDs
	stwio r22, (r23)
	
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer

	mov r22, r11
	.equ LEDs, 0xff200000
	movia r23, LEDs
	stwio r22, (r23)
	
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	call delaytimer
	
	br finish
	
endiloop: br endiloop

.data
TEST_NUM: .word 0x4a01fead, 0xF677D671,0xDC9758D5,0xEBBD45D2,0x8059519D
.word 0x76D8F0D2, 0xB98C9BB5, 0xD7EC3A9E, 0xD9BADC01, 0x89B377CD
.word 0 # end of list
LargestOnes: .word 0
LargestZeroes: .word 0
