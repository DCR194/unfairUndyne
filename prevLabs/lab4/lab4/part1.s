.global _start
_start:
	.equ LEDs, 0xff200000
	.equ Keys, 0xff200050
	movi r16, 1
	
	movia r8, LEDs
	movia r9, Keys
	movi r14, 15
	
	startLoop:
	
		ldwio r10, (r9)
		stwio r11, (r8)
		
		movi r15, 1
		beq r10, r15, resetCounter
		
		bgeu r11, r14, skipIncrease
		movi r15, 2
		beq r10, r15, increaseCounter
		
		skipIncrease:
		ble r11, r16, skipDecrease
		movi r15, 4
		beq r10, r15, decreaseCounter	
		
		skipDecrease:
		movi r15, 8
		beq r10, r15, blankCounter	
		
		br startLoop
		
	waitForReset:
		ldwio r10, (r9)		
		
		bne r10, r0, waitForReset
		br startLoop
	
	resetCounter: #1
		beq r11, r0, waitForReset
		movi r11, 1
		stwio r11, (r8)
		br waitForReset
		
	increaseCounter: #2
		addi r11, r11, 1
		stwio r11, (r8)
		br waitForReset
		
	
	decreaseCounter: #4
		subi r11, r11, 1
		stwio r11, (r8)
		br waitForReset
	
	blankCounter: #8
		movi r11, 0
		
		stwio r11, (r8)
		ldwio r10, (r9)
		beq r15, r10, blankCounter
		
		
		
		waitForOther:
		ldwio r10, (r9)
		
		beq r10, r15, waitForOther
		
		
		beq r10, r0, waitForOther
		
		
		
		movi r11, 1
		stwio r11, (r8)
		
		tempWait:
		ldwio r10, (r9)
		bne r10, r0, tempWait
		
		br startLoop
		
		
	
iloop: br iloop
	