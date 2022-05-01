.data
matrix: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25
.text
# This function calculates the address an element in a array of words
# Inputs:
#	 a0: The base address of the array
#	 a1: The index of the element
# Outputs:
#	 v0: The address of the element
array_element_address:
# C.1 goes here
	push ra
	
	li t0, 4  # Size of word
	mul t1, a1, t0
	add v0, t1, a0
	
	pop ra
	jr ra

# This function calculates the address of the element (i, j) in a matrix of words
# Inputs:
#	 a0: The base address of the matrix
#	 a1: The index (i) of the row
#	 a2: The index (j) of the column
#	 a3: The number of elements in a row
# Outputs:
#	 v0: The address of the element
matrix_element_address:  # Use this function in your project!
# C.2 goes here
	push ra
	
	li t0, 4  # Size of word
	mul t1, t0, a3  # Size of a row
	
	mul t2, t1, a1  # Row displacement
	mul t3, t0, a2  # Column displacement
	
	add t4, t2, t3  # Total displacement
	add v0, t4, a0  # address
	
	pop ra
	jr ra
	
.globl main
main:
# C.3 goes here
	
	li s0, 25
	_array_print:
		li s1, 0
		_array_print_loop:
			beq s1, s0, _array_print_end
			
			# Get address
			la a0, matrix
			move a1, s1
			jal array_element_address
			
			# Print num
			lw a0, (v0)
			li v0, 1
			syscall
			
			# Print space
			li a0, 32
			li v0, 11
			syscall
			
			# Increment counter						
			add s1, s1, 1
			
			j _array_print_loop
		_array_print_end:
			
# Print newlines
li a0, 10
li v0, 11
syscall
syscall

# C.4 goes here
	
	li s0, 5	# rows
	li s1, 5  # elem per row
	_m_print:
		li s2, 0
			_m_print_loop:
				li s3, 0
				# Done check
				beq s2, s0, _m_print_exit
				
				_m_print_row:
					
					# Done check
					beq s3, s1, _m_row_exit
					
					# Get address
					la a0, matrix
					move a1, s2  # row
					move a2, s3	 # column
					move a3, s1	 # size
					
					jal matrix_element_address
					
					# Print num
					lw a0, (v0)
					li v0, 1
					syscall
					
					# Print space
					li a0, 32
					li v0, 11
					syscall
					
					# Increment counter						
					add s3, s3, 1
					
					j _m_print_row
				_m_row_exit:
					# Increment counter						
					add s2, s2, 1
					
					# Print newline
					li a0, 10
					li v0, 11
					syscall
					
					j _m_print_loop
	_m_print_exit:
	
		li v0, 10
		syscall