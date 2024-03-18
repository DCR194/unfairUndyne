/******************************************************************************
 * Write an interrupt service routine
 *****************************************************************************/
.section .exceptions, "ax"
IRQ_HANDLER:
        # save registers on the stack (et, ra, ea, others as needed)
        subi    sp, sp, 16          # make room on the stack
        stw     et, 0(sp)
        stw     ra, 4(sp)
        stw     r20, 8(sp)

        rdctl   et, ctl4            # read exception type
        beq     et, r0, SKIP_EA_DEC # not external?
        subi    ea, ea, 4           # decrement ea by 4 for external interrupts

SKIP_EA_DEC:
        stw     ea, 12(sp)
        andi    r20, et, 0x2        # check if interrupt is from pushbuttons
        beq     r20, r0, END_ISR    # if not, ignore this interrupt
        call    KEY_ISR             # if yes, call the pushbutton ISR

END_ISR:
        ldw     et, 0(sp)           # restore registers
        ldw     ra, 4(sp)
        ldw     r20, 8(sp)
        ldw     ea, 12(sp)
        addi    sp, sp, 16          # restore stack pointer
        eret                        # return from exception

/*********************************************************************************
 * set where to go upon reset
 ********************************************************************************/
.section .reset, "ax"
        movia   r8, _start
        jmp    r8

/*********************************************************************************
 * Main program
 ********************************************************************************/
.equ Keys, 0xff200050

.text 
KEY_ISR:
	subi sp, sp, 4
	stw ra, (sp)
	subi sp, sp, 4
	stw r16, (sp)
	subi sp, sp, 4
	stw r17, (sp)
	
	
	
	movia r16, Keys
	ldwio r17, 0xc(r16)
	stwio r17, 0xc(r16)
	#stwio r0, 0x8(r16)
	
	
	
	mov r4, r17
	
	call convertToInput
	
	mov r4, r2 #r2 holds the number to be displayed
	
	mov r5, r3 #r3 holds the number of the register
	
	
	call HEX_DISP
	
	ldw r17, (sp)
	addi sp, sp, 4
	ldw r16, (sp)
	addi sp, sp, 4
	ldw ra, (sp)
	addi sp, sp, 4
	ret
	
#r4 contains the key input
convertToInput:
	subi sp, sp, 4
	stw ra, (sp)
		
	movi r5, 0b1000
	movi r2, 4
	beq r5, r4, finishConvert
	
	srli r5, r5, 1
	subi r2, r2, 1
	beq r5, r4, finishConvert
	
	srli r5, r5, 1
	subi r2, r2, 1
	beq r5, r4, finishConvert
	
	srli r5, r5, 1
	subi r2, r2, 1
	
	
	
	finishConvert:
	subi r3, r2, 1
	
	movia r7, currentState
	ldw r6, (r7)
	
	and r6, r6, r5
	
	beq r0, r6, skipBlank
	
	movi r2, 0b10000
	
	
	skipBlank:
	ldw r6, (r7)
	xor r6, r6, r5
	stw r6, (r7)
	ldw ra, (sp)
	addi sp, sp, 4
	
	ret
	
currentState: .word 0x0
	
.text
.global  _start
_start:
	movia sp, 0x400
	movia r8, Keys
	movia r3,0xf
  	stwio r3,8(r8)
	
	movi r2, 0xf
	stwio r2,12(r8)
  	wrctl ctl3,r2
	
	movia r2,1
    wrctl ctl0,r2 
        /*
        1. Initialize the stack pointer
        2. set up keys to generate interrupts
        3. enable interrupts in NIOS II
        */
IDLE:   br  IDLE




.equ HEX_BASE1, 0xff200020
.equ HEX_BASE2, 0xff200030

HEX_DISP:   movia    r8, BIT_CODES         # starting address of the bit codes
	    andi     r6, r4, 0x10	   # get bit 4 of the input into r6
	    beq      r6, r0, not_blank 
	    mov      r2, r0
	    br       DO_DISP
not_blank:  andi     r4, r4, 0x0f	   # r4 is only 4-bit
            add      r4, r4, r8            # add the offset to the bit codes
            ldb      r2, 0(r4)             # index into the bit codes

#Display it on the target HEX display
DO_DISP:    
			movia    r8, HEX_BASE1         # load address
			movi     r6,  4
			blt      r5,r6, FIRST_SET      # hex4 and hex 5 are on 0xff200030
			sub      r5, r5, r6            # if hex4 or hex5, we need to adjust the shift
			addi     r8, r8, 0x0010        # we also need to adjust the address
FIRST_SET:
			slli     r5, r5, 3             # hex*8 shift is needed
			addi     r7, r0, 0xff          # create bit mask so other values are not corrupted
			sll      r7, r7, r5 
			addi     r4, r0, -1
			xor      r7, r7, r4  
    			sll      r4, r2, r5            # shift the hex code we want to write
			ldwio    r5, 0(r8)             # read current value       
			and      r5, r5, r7            # and it with the mask to clear the target hex
			or       r5, r5, r4	           # or with the hex code
			stwio    r5, 0(r8)		       # store back
END:			
			ret
			

			
BIT_CODES:  .byte     0b00111111, 0b00000110, 0b01011011, 0b01001111
			.byte     0b01100110, 0b01101101, 0b01111101, 0b00000111
			.byte     0b01111111, 0b01100111, 0b01110111, 0b01111100
			.byte     0b00111001, 0b01011110, 0b01111001, 0b01110001

            .end
	

			

