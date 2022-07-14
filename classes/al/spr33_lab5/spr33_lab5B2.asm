.text
.globl main
main:
	li	s0, 0x1337BEEF
	li	s1, 0x00C0FFEE

	jal	function

	li	v0, 10
	syscall		# terminate program

function:
	li t0, 4
	
	sub sp, sp, t0
	sw ra, (sp)
	
	sub sp, sp, t0
	sw s0, (sp)
	
	sub sp, sp, t0
	sw s1, (sp)

	li	s0, 54
	addi	s1, s0, 100

	lw s1, (sp)
	add sp, sp, t0
	
	lw s0, (sp)
	add sp, sp, t0
	
	lw ra, (sp)
	add sp, sp, t0
	
	jr	ra