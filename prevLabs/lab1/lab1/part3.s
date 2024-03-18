.global _start
_start:

		# set up the registers
		# r1 will change its value
		movi r1, 0
		movi r2, 30
		
		# create loop label
		myLoop:
			addi r1, r1, 1
			add r12, r12, r1
			blt r1, r2, myLoop
		# if r1 < 30 run loop
	done: br done
	