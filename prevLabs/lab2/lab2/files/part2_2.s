.text  # The numbers that turn into executable instructions
.global _start
_start:

/* r13 should contain the grade of the person with the student number, -1 if not found */
/* r10 has the student number being searched */


	movia r10, 718293		# r10 is where you put the student number being searched for

/* Your code goes here  */
	movia r12, Snumbers
	movia r14, Grades
	movia r16, result
	
	
	ldw r11, (r12)
	ldb r15, (r14)
	movi r20, 0
	
	searchloop:
		
		beq r10, r11, numFound
		addi r12, r12, 4
		addi r14, r14, 1
		ldw r11, (r12)
		
		beq r11, r0, iloop
		ldb r15, (r14)
		br searchloop
		
	numFound:
		stb r15, (r16)
		
		

iloop: br iloop


.data  	# the numbers that are the data 

/* result should hold the grade of the student number put into r10, or
-1 if the student number isn't found */ 

result: .byte -1
		.skip 3
/* Snumbers is the "array," terminated by a zero of the student numbers  */
Snumbers: .word 10392584, 423195, 644370, 496059, 296800
        .word 265133, 68943, 718293, 315950, 785519
        .word 982966, 345018, 220809, 369328, 935042
        .word 467872, 887795, 681936, 0

/* Grades is the corresponding "array" with the grades, in the same order*/
Grades: .byte 99, 68, 90, 85, 91, 67, 80
        .byte 66, 95, 91, 91, 99, 76, 68  
        .byte 69, 93, 90, 72
	
	
