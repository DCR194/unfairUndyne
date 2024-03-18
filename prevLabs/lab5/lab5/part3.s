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
        beq     r20, r0, INCREMENT_LEDs    # if not, ignore this interrupt
        call    KEY_ISR             # if yes, call the pushbutton ISR
		
		
END_ISR:
        ldw     et, 0(sp)           # restore registers
        ldw     ra, 4(sp)
        ldw     r20, 8(sp)
        ldw     ea, 12(sp)
        addi    sp, sp, 16          # restore stack pointer
        eret                        # return from exception
		
INCREMENT_LEDs: 
	subi sp, sp, 12
	stw r16, 0(sp)
	stw r17, 4(sp)
	stw r18, 8(sp)
	
	movia r17, RUN
	ldw r18, (r17)
	
	movia r17, COUNT
	ldw r16, (r17)
	
	andi r16, r16, 0x3ff
	add  r16, r16, r18
	
	stw r16, (r17)
	
	movia r16, statusReg
	movia r17, 0b10
	stwio r17, (r16)
	
	ldw r16, 0(sp)
	ldw r17, 4(sp)
	ldw r18, 8(sp)
	addi sp, sp, 12
	
	br END_ISR
	
KEY_ISR:
	subi sp, sp, 8
	stw r8, 0(sp)
	stw r9, 4(sp)
	
	subi sp, sp, 4
	stw ra, (sp)
	
	movia     r8, edgeReg
    ldwio     r9, (r8)
    andi     r9, r9, 0xf
    stwio     r9, (r8)
	
	movia r8, RUN
	ldw r9, (r8)
	
	xori r9, r9, 0x1
	
	stw r9, (r8)
	
	ldw ra, (sp)
	addi sp, sp, 4
	

	ldw r8, 0(sp)
	ldw r9, 4(sp)
	addi sp, sp, 8
	
	ret

.text
.global  _start
_start:
    /* Set up stack pointer */
	movia sp, 0x400

    call    CONFIG_TIMER        # configure the Timer

    call    CONFIG_KEYS         # configure the KEYs port

    /* Enable interrupts in the NIOS-II processor */
	movi r8,1
    wrctl ctl0,r8
	

    movia   r8, LEDs        # LEDR base address (0xFF200000)
    movia   r9, COUNT           # global variable
LOOP:
    ldw     r10, 0(r9)          # global variable
    stwio   r10, 0(r8)          # write to the LEDR lights
    br      LOOP

CONFIG_TIMER:              # code not shown

	subi sp, sp, 12
	stw r8, 0(sp)
	stw r9, 4(sp)
	stw r10, 8(sp)
	

	#17D7840
	movia r8, counterLow
	movia r10, 0x7840 
	stwio r10, (r8)
	movia r8, counterHigh
	movia r10, 0x17D
	stwio r10, (r8)
	
	movia r8, controlReg
	movi r9, 0b111 # activate counter and start
	stwio r9, (r8)
	
	movia r8, statusReg
	movia r10, 2
	stwio r10, (r8)
	
	ldw r8, 0(sp)
	ldw r9, 4(sp)
	ldw r10, 8(sp)
	addi sp, sp, 12
	
	ret
	
CONFIG_KEYS:               # code not shown

	subi sp, sp, 12
	stw r8, 0(sp)
	stw r9, 4(sp)
	stw r10, 8(sp)
	
	
	
	movia r8, Keys
	movia r9,0xf
  	stwio r9,8(r8)
	
	movi r10, 0xf
	stwio r10,12(r8)
  	wrctl ctl3,r10
	
	ldw r8, 0(sp)
	ldw r9, 4(sp)
	ldw r10, 8(sp)
	addi sp, sp, 12
	

	ret


.data
/* Global variables */
.global  COUNT
COUNT:  .word    0x0            # used by timer

.global  RUN                    # used by pushbutton KEYs
RUN:    .word    0x1            # initial value to increment COUNT

.equ statusReg, 0xff202000
.equ counterLow, 0xff202008
.equ counterHigh, 0xff20200c
.equ controlReg, 0xff202004
.equ LEDs, 0xff200000
.equ edgeReg, 0xFF20005C
.equ Keys, 0xff200050

.end 