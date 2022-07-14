## This file implements the functions that control the pixels based on the keyboard input

# Include the macros file so that we save some typing! :)
.include "macros.asm"
# Include the constants settings file with the board settings! :)
.include "constants.asm"
# We will need to access the pixel model, include the structure offset definitions
.include "structs.asm"

# This function needs to be called by other files, so it needs to be global
.globl update_game


.text

# Master function
update_game:
	push ra
	
	
	lw t0, frame_counter
	li t1, 15
	div t0, t1
	mfhi t2
	bnez t2, _skip_moves
	
	# Move player (manage collisions) (15 slowed)
	jal move_player
	
 	# Move enemies (15 slowed)
 	jal move_enemies
 	
 	_skip_moves:

	# Propagate explosion
	lw t0, frame_counter
	li t1, 5
	div t0, t1
	mfhi t2
	bnez t2, _skip_prop
	
	jal prop_exp
	
	_skip_prop:
	# Tick bomb
	lw t1, bombIsActive
	beqz t1, _no_tick
	
	jal tick_bomb
	
	_no_tick:
	
	# If b pressed and no bomb, place bomb
	lw t0, b_pressed
	lw t1, bombIsActive
	
	beqz t0, _no_bomb
	bnez t1, _no_bomb
	
	jal place_bomb
	
	_no_bomb:
	
	# Check player/exp
	jal player_exp
	bnez v0, _loss
	
	# Check enemy/exp
	jal enemies_exp
	
	# Check block/exp
	jal des_exp
	
	# Check enemy/player
	jal player_enemy
	bnez v0, _loss
	
	# Check all enemies dead
	jal are_enemies_dead
	bnez v0, _win
	
	_continue:
	li v0, 0
	j _end
	_win:
	li v0, 1
	j _end
	_loss:
	li v0, 2
	_end:
	pop ra
	jr ra
# end update_game


# Check no more enemies
are_enemies_dead:
	push ra
	push s0
	
	# Iterate through the number of enemies
	li s0, 0
	_loop:
	
		li t0, n_enemies
		beq t0, s0, _none_found_alive
	
		move a0, s0
		jal get_enemy_element
		
		# Get active
		lw t0, enemy_active(v0)
		li t1, 1
		beq t0, t1, _found_alive
		
		addi s0, s0, 1
		j _loop
		
	_found_alive:
	li v0, 0
	j _end
	
	_none_found_alive:
	li v0, 1
	
	_end:
	pop s0
	pop ra
	jr ra
# end are_enemies_dead

# Check player/enemy collision
player_enemy:
	push ra
	push s0
	li s0, 0
	_loop:
	
		li t0, n_enemies
		beq t0, s0, _nocol
	
		move a0, s0
		jal get_enemy_element
		
		lw t0, enemy_x(v0)
		lw t1, enemy_y(v0)
		lw t2, enemy_active(v0)
		beqz t2, _continue
		
		# Check
		lw t2, playerx
		lw t3, playery
		bne t0, t2, _continue
		bne t1, t3, _continue
		
		j _col
		
		
		_continue:
		addi s0, s0, 1
		j _loop
	
	_col:
	li v0, 1
	j _end
	
	_nocol:
	li v0, 0
	_end:
	pop s0
	pop ra
	jr ra
# end player_enemy

# Check player/explosion collision
player_exp:
	push ra
	push s0
	
	lw t0, expIsActive
	beqz t0, _out
	
	lw s0, expRadius
	
	_check_x:
	lw t0, playerx
	lw t1, expx
	
	bgt t0, t1, _exp_behind
	_exp_ahead:
	sub t2, t1, t0
	bge t2, s0, _out
	j _check_y
	_exp_behind:
	sub t2, t0, t1
	bge t2, s0, _out
	
	_check_y:
	lw t0, playery
	lw t1, expy
	bge t0, t1, _exp_behind2
	_exp_ahead2:
	sub t2, t1, t0
	bge t2, s0, _out
	j _in
	_exp_behind2:
	sub t2, t0, t1
	bgt t2, s0, _out
		
	_in:
	li v0, 1
	j _end
	_out:
	li v0, 0
	_end:
	pop s0
	pop ra
	jr ra
# end player_exp

# Check enemy/explosion collision
# a0: enemy element
enemy_exp:
	push ra
	push s0
	push s1
	
	move s1, a0
	
	lw t0, expIsActive
	beqz t0, _out
	
	lw s0, expRadius
	
	_check_x:
	lw t0, enemy_x(s1)
	lw t1, expx
	
	bgt t0, t1, _exp_behind
	_exp_ahead:
	sub t2, t1, t0
	bge t2, s0, _out
	j _check_y
	_exp_behind:
	sub t2, t0, t1
	bge t2, s0, _out
	
	_check_y:
	lw t0, enemy_y(s1)
	lw t1, expy
	bge t0, t1, _exp_behind2
	_exp_ahead2:
	sub t2, t1, t0
	bge t2, s0, _out
	j _in
	_exp_behind2:
	sub t2, t0, t1
	bgt t2, s0, _out
		
	_in:
	li t0, 0
	sw t0, enemy_active(s1)
	j _end
	_out:
	_end:
	pop s1
	pop s0
	pop ra
	jr ra
# end enemy_exp

# Iterated enemy explosion check
enemies_exp:
	push ra
	push s0
	li s0, 0
	_loop:
	
		li t0, n_enemies
		beq t0, s0, _end
	
		move a0, s0
		jal get_enemy_element
		
		move a0, v0
		jal enemy_exp
		
		_continue:
		addi s0, s0, 1
		j _loop
	
	_end:
	
	pop s0
	pop ra
	jr ra
# end enemies_exp

# Check des/explosion collision
des_exp:
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
	jal remove_block
	
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
		jal remove_block
		
		# down
		move a0, s1
		add a1, s2, s0
		jal remove_block
		
		# left
		sub a0, s1, s0
		move a1, s2
		jal remove_block
		
		# right
		add a0, s1, s0
		move a1, s2
		jal remove_block
		
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
# end des_exp

# Place bomb
place_bomb:
	push ra
	
	lw t0, playerx
	lw t1, playery
	li t2, 1
	li t3, BOMB_TIME
	
	sw t0, bombx
	sw t1, bomby
	sw t2, bombIsActive
	sw t3, bombTime
	
	pop ra
	jr ra

# Bomb ticks
tick_bomb:
	push ra
	
	lw t0, bombTime
	
	beqz t0, _start_exp
	subi t0, t0, 1
	sw t0, bombTime
	j _end
	
	_start_exp:
	jal spawn_explosion
	
	_end:
	pop ra
	jr ra
# end tick_bomb

# Bomb explodes
spawn_explosion:
	push ra
	
	li t0, 0
	sw t0, bombIsActive
	
	li t0, 1
	sw t0, expIsActive
	
	li t0, 0
	sw t0, expRadius
	
	lw t0, bombx
	lw t1, bomby
	sw t0, expx
	sw t1, expy
	
	pop ra
	jr ra
# end spawn_explosion

# Explosion propagates/disappears
prop_exp:
	push ra
	
	lw t0, expRadius
	blt t0, 3, _prop
	
	li t0, 0
	sw t0, expIsActive
	sw t0, expRadius
	
	j _end
	_prop:
	lw t0, expRadius
	addi t0, t0, 1
	sw t0, expRadius
	
	_end:
	pop ra
	jr ra
# end prop_exp

# Player moves
move_player:
	push ra
	
	# Check up
	_check_up:

	lw t0, playerx
	lw t1, playery
	lw t2, up_pressed
	beqz t2, _check_down
	
	move a0, t0
	subi a1, t1, 1
	jal is_open
	beqz v0, _check_down
	
	# Move up
	lw t1, playery
	subi t1, t1, 1
	sw t1, playery
	
	# Check down
	_check_down:
	
	lw t0, playerx
	lw t1, playery
	lw t2, down_pressed
	beqz t2, _check_right
	
	move a0, t0
	addi a1, t1, 1
	jal is_open
	beqz v0, _check_right
	
	# Move down
	lw t1, playery
	addi t1, t1, 1
	sw t1, playery

	# Check right
	_check_right:
	
	lw t0, playerx
	lw t1, playery
	lw t2, right_pressed
	beqz t2, _check_left
	
	addi a0, t0, 1
	move a1, t1
	jal is_open
	beqz v0, _check_left
	
	# Move right
	lw t0, playerx
	addi t0, t0, 1
	sw t0, playerx
	
	# Check left
	_check_left:
	
	lw t0, playerx
	lw t1, playery
	lw t2, left_pressed
	beqz t2, _exit
	
	subi a0, t0, 1
	move a1, t1
	jal is_open
	beqz v0, _exit
	
	# Move left
	lw t0, playerx
	subi t0, t0, 1
	sw t0, playerx
	
	_exit:
	pop ra
	jr ra
# end move_player

# Enemies move
move_enemies:
	push ra
	push s0
	push s1
	push s2
	
	# Iterate through the number of enemies
	li s0, 0
	_loop:
	
		li t0, n_enemies
		beq t0, s0, _end
	
		move a0, s0
		jal get_enemy_element
		
		move s1, v0
		lw t0, enemy_active(s1)
		beqz t0, _continue
		
		# Move enemy
		li a0, 0
		li a1, 4
		li v0, 42
		syscall
		
		beq v0, 0, _up
		beq v0, 1, _down
		beq v0, 2, _right
		beq v0, 3, _left
		
		_up:
		
		lw a0, enemy_x(s1)
		lw a1, enemy_y(s1)
		subi a1, a1, 1
		jal is_open
		beqz v0, _continue
		lw a1, enemy_y(s1)
		subi a1, a1, 1
		sw a1, enemy_y(s1)
		
		j _continue
		_down:
		
		lw a0, enemy_x(s1)
		lw a1, enemy_y(s1)
		addi a1, a1, 1
		jal is_open
		beqz v0, _continue
		lw a1, enemy_y(s1)
		addi a1, a1, 1
		sw a1, enemy_y(s1)
		
		j _continue
		_left:
		
		lw a0, enemy_x(s1)
		lw a1, enemy_y(s1)
		subi a0, a0, 1
		jal is_open
		beqz v0, _continue
		lw a0, enemy_x(s1)
		subi a0, a0, 1
		sw a0, enemy_x(s1)
		
		j _continue
		_right:
		
		lw a0, enemy_x(s1)
		lw a1, enemy_y(s1)
		addi a0, a0, 1
		jal is_open
		beqz v0, _continue
		lw a0, enemy_x(s1)
		addi a0, a0, 1
		sw a0, enemy_x(s1)
		
		_continue:
		addi s0, s0, 1
		j _loop
	
	_end:
	pop s2
	pop s1
	pop s0
	pop ra
	jr ra
# end move_enemies

# Remove destructible
remove_block:
	push ra
	push s0
	push s1
	
	move s0, a0
	move s1, a1
	
	blt s0, 0, _end
	blt s1, 0, _end
	bge s0, BOARD_LENGTH, _end
	bge s1, BOARD_LENGTH, _end
	
	move a0, s0
	move a1, s1
	jal get_board_element
	li t0, 1
	beq v0, t0, _remove
	
	j _end
	
	_remove:
	move a0, s0
	move a1, s1
	li a2, 0
	jal set_board_element
	
	_end:
	pop s1
	pop s0
	pop ra
	jr ra
