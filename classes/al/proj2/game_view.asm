## This file implements the functions that display the pixels based on the model

# Include the macros file so that we save some typing! :)
.include "macros.asm"
# Include the constants settings file with the board settings! :)
.include "constants.asm"
# We will need to access the pixel model, include the structure offset definitions
.include "structs.asm"

.globl display_game

.data
	DES_BLOCK: .byte		COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN,
											COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN,
											COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN,
											COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN,
											COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN
									
	EXP_BLOCK: .byte		COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
											COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
											COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
											COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
											COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED
									
	PLAYER_BLOCK: .byte	COLOR_BLUE, COLOR_BLUE, COLOR_NONE, COLOR_BLUE, COLOR_BLUE,
											COLOR_BLUE, COLOR_BLUE, COLOR_NONE, COLOR_BLUE, COLOR_BLUE,
											COLOR_NONE, COLOR_NONE, COLOR_BLUE, COLOR_NONE, COLOR_NONE,
											COLOR_NONE, COLOR_NONE, COLOR_BLUE, COLOR_NONE, COLOR_NONE,
											COLOR_NONE, COLOR_BLUE, COLOR_NONE, COLOR_BLUE, COLOR_NONE
									
	INDES_BLOCK: .byte	COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN,
											COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN,
											COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN,
											COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN,
											COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN, COLOR_TAN
									
	ENEMY_BLOCK: .byte	COLOR_PURPLE, COLOR_PURPLE, COLOR_NONE, COLOR_PURPLE, COLOR_PURPLE,
											COLOR_PURPLE, COLOR_PURPLE, COLOR_NONE, COLOR_PURPLE, COLOR_PURPLE,
											COLOR_PURPLE, COLOR_PURPLE, COLOR_NONE, COLOR_PURPLE, COLOR_PURPLE,
											COLOR_PURPLE, COLOR_PURPLE, COLOR_NONE, COLOR_PURPLE, COLOR_PURPLE,
											COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE
									
	BOMB_BLOCK: .byte		COLOR_NONE, 	COLOR_NONE, 	COLOR_NONE, 	COLOR_NONE, 	COLOR_NONE,
											COLOR_NONE, 	COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_NONE,
											COLOR_NONE, 	COLOR_ORANGE, COLOR_RED, 	COLOR_ORANGE, COLOR_NONE,
											COLOR_NONE, 	COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_NONE,
											COLOR_NONE, 	COLOR_NONE, 	COLOR_NONE, 	COLOR_NONE, 	COLOR_NONE

.text

# Master display drawing function
display_game:
	push ra
	
	jal display_border
	jal display_blocks
	jal display_player
	jal display_enemies
	jal display_bomb
	jal display_exp
	
	pop ra
	jr ra
# end display_update

# Display border
display_border:
	push ra
	
	# TODO
	
	pop ra
	jr ra
# end display_border

# Display blocks
display_blocks:
	push ra
	push s0
	push s1
	
	# Iterate through board
	li s0, 0
	_x_loop:
		beq s0, BOARD_LENGTH, _x_loop_end
		li s1, 0
		_y_loop:
			beq s1, BOARD_LENGTH, _y_loop_end
			
			# Get board value and display it
			move a0, s0
			move a1, s1
			jal get_board_element
			move a0, s0
			move a1, s1
			beq v0, 1, _print_des
			beq v0, 2, _print_indes
			j _next
			
			_print_des:
			
			la a2, DES_BLOCK
			jal blit_logical
			
			
			j _next
			_print_indes:
			
			la a2, INDES_BLOCK
			jal blit_logical
			
			_next:
			
			addi s1, s1, 1
			j _y_loop
			
		_y_loop_end:
		addi s0, s0, 1
		j _x_loop
		
	_x_loop_end:
	
	pop s1
	pop s0
	pop ra
	jr ra
# end display_blocks

# Display player
display_player:
	push ra
	
	lw a0, playerx
	lw a1, playery
	la a2, PLAYER_BLOCK
	jal blit_trans_logical
	
	pop ra
	jr ra
# end display_player

# Display enemies
display_enemies:
	push ra
	push s0
	
	# Iterate through the number of enemies
	li s0, 0
	# Iterate through the number of enemies
	li s0, 0
	_loop:
	
		li t0, n_enemies
		beq t0, s0, _end
	
		move a0, s0
		jal get_enemy_element
		
		lw a0, enemy_x(v0)
		lw a1, enemy_y(v0)
		lw t2, enemy_active(v0)
		la a2, ENEMY_BLOCK
		
		beqz t2, _continue
		
		# Disp enemy
		jal blit_trans_logical
		
		_continue:
		addi s0, s0, 1
		j _loop
	
	_end:
	pop s0
	pop ra
	jr ra
# end display_enemies

# Display bomb
display_bomb:
	push ra
	
	lw a0, bombx
	lw a1, bomby
	lw t2, bombIsActive
	beqz t2, _end
	
	la a2, BOMB_BLOCK
	jal blit_trans_logical
	
	_end:
	pop ra
	jr ra
# end display_bomb

# Display exp
display_exp:
	push ra
	push s0
	push s1
	push s2
	push s3
	
	lw t0, expIsActive
	beqz t0, _end
	
	# draw dot
	lw a0, expx
	lw a1, expy
	la a2, EXP_BLOCK
	jal blit_logical
	
	# draw out
	li s0, 0
	lw s3, expRadius
	_out_loop:
		beq s0, s3, _end_out
		
		lw s1, expx
		lw s2, expy
		
		# up
		move a0, s1
		sub a1, s2, s0
		la a2, EXP_BLOCK
		jal blit_logical
		
		# down
		move a0, s1
		add a1, s2, s0
		la a2, EXP_BLOCK
		jal blit_logical
		
		# left
		sub a0, s1, s0
		move a1, s2
		la a2, EXP_BLOCK
		jal blit_logical
		
		# right
		add a0, s1, s0
		move a1, s2
		la a2, EXP_BLOCK
		jal blit_logical
		
		addi s0, s0, 1
		j _out_loop
		
	_end_out:
	
	
	_end:
	pop s3
	pop s2
	pop s1
	pop s0
	pop ra
	jr ra
# end display_exp


# Blit trans logical
blit_trans_logical:
	push ra
	
	blt a0, 0, _end
	blt a1, 0, _end
	bge a0, 11, _end
	bge a1, 11, _end
	
	mul a0, a0, 5
	mul a1, a1, 5
	jal display_blit_5x5_trans
	
	_end:
	pop ra
	jr ra
# end blit_trans_logical

# Blit logical
blit_logical:
	push ra
	
	blt a0, 0, _end
	blt a1, 0, _end
	bge a0, 11, _end
	bge a1, 11, _end
	
	mul a0, a0, 5
	mul a1, a1, 5
	jal display_blit_5x5
	
	_end:
	pop ra
	jr ra
# end blit_logical
	



