# Name: Shane Riley (spr33)
# Class: CS 0447
# Project 1: Connect 4
# Mainloop pseudocode
#class Connect {
#    public static void main(String args[]) {
#        int[][] board = new int[6][7];
#        printWelcome();
#
#        int player = 1;
#        while(true) {
#
#            // Print board
#            print();
#
#            // Get column
#            int column = -1;
#            while(!checkColumn(board, column))
#                column = promptForColumn();
#            
#            int row = placePiece(board, player, column);
#            if (checkWin(board, row, column, player)) {
#                win(player)
#            }
#            if (checkFull(board))
#                full();
#            // Switch player
#            player = (player==1) ? 2 : 1;
#        }
#    }
#}

.data
	board: .word
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
	
	intro: .asciiz "Welcome to Shane's Connect-4 in MIPS!\nTake turns placing tokens, and create a line of 4 to win!\nGood luck!\n\n"
	annoy: .asciiz "Try again!\n"
	prompt: .asciiz "Select a column between 0 and 6: "
	p1win: .asciiz "Player 1 Wins!\nThanks for playing!"
	p2win: .asciiz "Player 2 Wins!\nThanks for playing!"
	full: .asciiz "Board is full!\nTie game!"
	topString: .asciiz " 0 1 2 3 4 5 6\n"
	
.text

# get value from ij
get_value:
	# a0: i
	# a1: j
	# a2: num columns
	# v0: value (0,1,2)
	
	push ra
	
	# Get internal logical address
	mul t0, a0, a2
	move t1, a1
	add t2, t1, t0
	
	# Handle word size
	mul t2, t2, 4
	
	# Get location in memory
	la t3, board
	add t3, t3, t2
	
	# Grab value
	lw v0, (t3)
	
	pop ra
	jr ra
# end get_value

# set value from ij
set_value:
	# a0: i
	# a1: j
	# a2: num columns
	# a3: value to place
	
	push ra
	
	# Get internal logical address
	mul t0, a0, a2
	move t1, a1
	add t2, t1, t0
	
	# Handle word size
	mul t2, t2, 4
	
	# Get location in memory
	la t3, board
	add t3, t3, t2
	
	# Set value
	sw a3, (t3)
	
	pop ra
	jr ra
# end get_value


# print board
print:
	push ra
	push s0
	push s1
	
	# Topstring
	li v0, 4
	la a0, topString
	syscall
	
	# Loop through i (start at highest)
	li s0, 5
	_i_loop:
		
		bltz s0, _i_loop_exit
		
		# Print pipe
		li v0, 11
		li a0, 0x7c
		syscall
		
		# Loop through j (start at left)
		li s1, 0
		_j_loop:
			bgt s1, 6, _j_loop_exit
			
			# Print value
			move a0, s0
			move a1, s1
			li a2, 7
			jal get_value
			move t7, v0
			
			# Print integer
			li v0, 1
			move a0, t7
			syscall
			
			# Print pipe
			li v0, 11
			li a0, 0x7c
			syscall
			
			# Iterate
			addi s1, s1, 1
			j _j_loop
			
		_j_loop_exit:
			
		# newline
		li v0, 11
		li a0, 0x0A
		syscall
		
		# Iterate
		subi s0, s0, 1
		j _i_loop
		
	_i_loop_exit:
	
	# newline
	li v0, 11
	li a0, 0x0A
	syscall
	
	pop s1
	pop s0
	pop ra
	jr ra
# end print

# validate input
validate_input:
	# a0: input column
	# v0: zero if okay to place
	
	push ra
	push s0
	
	move s0, a0
	
	# Check range
	blt s0, 0, _bad_input
	bgt s0, 6, _bad_input
	
	# Check full column
	move a0, s0
	jal check_full_column
	beqz v0, _bad_input
	
	# Good input
	li v0, 0
	j _end
	
	_bad_input:
		li v0, 1
	
	_end:
	pop s0
	pop ra
	jr ra
# end validate_input

# add piece
add_piece:
	# a0 to play
	# a1 column to place
	# v0 row placed
	push ra
	push s0
	push s1
	push s2
	
	# Start at i=0
	li s0, 0
	move s2, a0
	move s1, a1
	
	_i_loop:
		move a0, s0
		move a1, s1
		li a2, 7
		jal get_value
		beqz v0, _row_found
		addi s0, s0, 1
		j _i_loop
	
	_row_found:
	
	move v0, s0
	move a0, s0
	move a1, s1
	li a2, 7
	move a3, s2
	jal set_value
	
	_end:
	pop s2
	pop s1
	pop s0
	pop ra
	jr ra
# end add_piece

# check win
check_win:
	# a0: i
	# a1: j
	# a2: to play
	# v0: is win for 1, 2, 0 is nowin
	
	push ra
	push s0
	push s1
	push s2
	push s3
	push s4
	move s0, a0
	move s1, a1
	move s2, a2
	
	
	_check_down:
	blt s0, 3, _check_sides
	
	# Check three below
	move s3, s0
	li s4, 0
	_down_loop:
		bgt s4, 2, _win
		
		move a0, s3
		move a1, s1
		li a2, 7
		jal get_value
		bne v0, s2, _check_sides
		
		subi s3, s3, 1
		addi s4, s4, 1
		j _down_loop
	
	_check_sides:
	
	li s3, 0  # num in sides
	
	li s4, 1  # num away laterally
	_right_loop:
		
		# Check bounds
		add t0, s4, s1
		bgt t0, 6, _left_loop_start
		
		# Get value
		move a0, s0
		move a1, t0
		li a2, 7
		jal get_value
		
		# Check done
		bne v0, s2, _left_loop_start
		
		# Add
		addi s3, s3, 1
		addi s4, s4, 1
		
		j _right_loop
		
	_left_loop_start:
	li s4, 1  # num away laterally
	_left_loop:
	
		# Check bounds
		sub t0, s1, s4
		blt t0, 0, _done_sides
		
		# Get value
		move a0, s0
		move a1, t0
		li a2, 7
		jal get_value
		
		# Check done
		bne v0, s2, _done_sides
		
		# Add
		addi s3, s3, 1
		addi s4, s4, 1
		
		j _left_loop
	
	_done_sides:
	
		bge s3, 3, _win
		
	_check_upright:
	
	li s3, 0  # num in sides
	li s4, 1  # num away laterally
	_upright_loop:
		
		# Check bounds
		add t0, s4, s0
		add t1, s4, s1
		bgt t0, 5, _downleft_loop_start
		bgt t1, 6, _downleft_loop_start
		
		# Get value
		move a0, t0
		move a1, t1
		li a2, 7
		jal get_value
		
		# Check done
		bne v0, s2, _downleft_loop_start
		
		# Add
		addi s3, s3, 1
		addi s4, s4, 1
		
		j _upright_loop
		
	_downleft_loop_start:
	li s4, 1  # num away laterally
	_downleft_loop:
	
		# Check bounds
		sub t0, s0, s4
		sub t1, s1, s4
		blt t0, 0, _done_upright
		blt t1, 0, _done_upright
		
		# Get value
		move a0, t1
		move a1, t0
		li a2, 7
		jal get_value
		
		# Check done
		bne v0, s2, _done_upright
		
		# Add
		addi s3, s3, 1
		addi s4, s4, 1
		
		j _downleft_loop
	
	_done_upright:
	
		bge s3, 3, _win
		
	_check_downright:
	
	li s3, 0  # num in sides
	li s4, 1  # num away laterally
	_downright_loop:
		
		# Check bounds
		add t0, s4, s0
		sub t1, s1, s4
		bgt t0, 5, _upleft_loop_start
		blt t1, 0, _upleft_loop_start
		
		# Get value
		move a0, t0
		move a1, t1
		li a2, 7
		jal get_value
		
		# Check done
		bne v0, s2, _upleft_loop_start
		
		# Add
		addi s3, s3, 1
		addi s4, s4, 1
		
		j _downright_loop
		
	_upleft_loop_start:
	li s4, 1  # num away laterally
	_upleft_loop:
	
		# Check bounds
		sub t0, s0, s4
		add t1, s1, s4
		blt t0, 0, _done_upleft
		bgt t1, 6, _done_upleft
		
		# Get value
		move a0, t1
		move a1, t0
		li a2, 7
		jal get_value
		
		# Check done
		bne v0, s2, _done_upleft
		
		# Add
		addi s3, s3, 1
		addi s4, s4, 1
		
		j _upleft_loop
	
	_done_upleft:
	
		bge s3, 3, _win

	_nowin:
	li v0, 0
	j _end
	
	_win:
	move v0, s2

	_end:
	pop s4
	pop s3
	pop s2
	pop s1
	pop s0
	pop ra
	jr ra
# end check_win

# check full
check_full:
	push ra
	push s0
	
	# Iterate j
	li s0, 0
	_j_loop:
		bgt s0, 6, _is_full
		
		move a0, s0
		jal check_full_column
		bnez v0, _is_not_full
		
		addi s0, s0, 1
		j _j_loop
	
	_is_full:
	li v0, 0
	
	j _end
	
	_is_not_full:
	li v0, 1
	
	_end:
	pop s0
	pop ra
	jr ra
# end check_full

# check full column
check_full_column:
	# a0: column number
	# v0: is column full
	
	push ra
	push s0
	push s1
	
	move s1, a0
	
	# Iterate i
	li s0, 0
	
	_loop:
		bgt s0, 5, _is_full
		
		# Check spot
		move a0, s0
		move a1, s1
		li a2, 7
		jal get_value
		beqz v0, _is_not_full
		
		addi s0, s0, 1
		j _loop

	_is_full:
		li v0, 0
		j _end
		
	_is_not_full:
		li v0, 1
		
	_end:
	pop s1
	pop s0
	pop ra
	jr ra
# end check_full_column

# main
.globl main
main:
	
	# Print intro
	li v0, 4
	la a0, intro
	syscall
	
	# s1 is player to play
	li s1, 1
	_gameloop:
	
		# Print board
		jal print
		
		
		_prompt_loop:
		
			# Prompt for move
			li v0, 4
			la a0, prompt
			syscall
			
			# Gather input into s2
			li v0, 5
			syscall
			move s2, v0
	
			# Validate input
			move a0, s2
			jal validate_input
			bnez v0, _prompt_loop
		
		_place_piece:
		
			# Place the piece
			move a0, s1  # to play
			move a1, s2  # column chosen
			jal add_piece
			move s3, v0
			
		_check_win:
		
			# Check win for player s1
			move a0, s3
			move a1, s2
			move a2, s1
			jal check_win
			beq v0, 1, _p1win
			beq v0, 2, _p2win
			
		_check_full:
		
			# Check for full board
			jal check_full
			beqz v0, _full
		
		# Switch player
		beq s1, 1, _p2_n
		beq s1, 2, _p1_n
		
		_p1_n:
		li s1, 1
		
		j _continue
		_p2_n:
		li s1, 2
		
		_continue:
		j _gameloop
		
	_full:
	
	# Print full
	li v0, 4
	la a0, full
	syscall
	
	j _end
	
	_p1win:
	
	# Print win
	li v0, 4
	la a0, p1win
	syscall
	
	j _end
	
	_p2win:
	
	# Print win
	li v0, 4
	la a0, p2win
	syscall
	
	j _end
	
	_end:
	
	# End program
	li v0, 10
	syscall
