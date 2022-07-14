.data

	intString: .asciiz "Moving disk "
	fromString: .asciiz " from "
	toString: .asciiz " to "
	newline: .asciiz "\n"

.text
.globl main
main:

	li	a0, 5
	li	a1, 'L'
	li	a2, 'R'
	li	a3, 'C'
	
	# call solve_hanoi here
	jal solve_hanoi

	li	v0, 10
	syscall

# a0 - height of the tower
# a1 - source pole
# a2 - destination pole
# a3 - auxiliary pole
solve_hanoi:
	# your code goes here
	push ra
	push s0
	push s1
	push s2
	push s3
	
	# Save values in s
	move s0, a0
	move s1, a1
	move s2, a2
	move s3, a3
	
	beq a0, zero, _solve_hanoi_return
	
	# Setup recursive call
	# Lower n
	sub a0, s0, 1
	
	# switch aux and dest
	move a1, s1
	move a2, s3
	move a3, s2
	
	# call function
	jal solve_hanoi
	
	# Print using s
	
	la a0, intString
	li v0, 4
	syscall
	
	move a0, s0
	li v0, 1
	syscall
	
	la a0, fromString
	li v0, 4
	syscall
	
	move a0, s1
	li v0, 11
	syscall
	
	la a0, toString
	li v0, 4
	syscall
	
	move a0, s2
	li v0, 11
	syscall
	
	la a0, newline
	li v0, 4
	syscall
	
	# Call solve hanoi again
	sub a0, s0, 1
	move a1, s3
	move a2, s2
	move a3, s1
	jal solve_hanoi
	
_solve_hanoi_return:
	
	pop s3
	pop s2
	pop s1
	pop s0
	pop ra
	jr ra
	