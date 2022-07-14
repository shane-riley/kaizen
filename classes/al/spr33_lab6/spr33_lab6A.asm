.text

get_bit:
	# Finds bit at location in a number
	# a0: number
	# a1: index
	# v0: bit
	
	# Right shift a0 a1 times (fill with zeros)
	srlv a0, a0, a1

	# Return as v0
	move v0, a0
	
	jr ra
# end get_bit

set_bit:
	# Turns on a bit in a0, with a1 set to 1
	# a0: number
	# a1: index
	# v0: number with bit
	
	# Make the mask
	li t0, 1
	sllv t0, t0, a1
	
	# Combine using or
	or v0, a0, t0
	
	jr ra
# end set_bit

reset_bit:
	# Turns on a bit in a0, with a1 set to 0
	# a0: number
	# a1: index
	# v0: number with bit
	
	# Make the mask
	li t0, 1
	sllv t0, t0, a1
	not t0, t0
	
	# Combine using and
	and v0, a0, t0
	
	jr ra
# end reset_bit

invert_case:
	# Switch upper and lower case characters
	# a0: string
	# v0: modified string
	
	# Foreach char, if uppercase add 20 hex, if lowercase sub 20 hex, else do nothing
	
	# internal index
	li t0, 0
	
	_invert_case_loop:
	
	# mem location
	add t1, a0, t0
	
	# Get character
	lb t2, (t1)
	
	# End check
	beqz t2, _invert_case_loop_exit
	
	# lowercase check
	blt t2, 0x61, _skip_lower
	bgt t2, 0x7A, _skip_lower
	
	subi t2, t2, 0x20
	sb t2, (t1)
	j _skip_upper
	
	_skip_lower:
	# Uppercase check
	blt t2, 0x41, _skip_upper
	bgt t2, 0x5A, _skip_upper
	
	addi t2, t2, 0x20
	sb t2, (t1)
	
	_skip_upper:
	# Iterate
	addi t0, t0, 1
	j _invert_case_loop
	_invert_case_loop_exit:
	
	move v0, a0
	
	jr ra
# end invert_case
