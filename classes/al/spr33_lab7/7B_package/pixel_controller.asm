## This file implements the functions that control the pixels based on the keyboard input

# Include the macros file so that we save some typing! :)
.include "macros.asm"
# Include the constants settings file with the board settings! :)
.include "constants.asm"
# We will need to access the pixel model, include the structure offset definitions
.include "pixel_struct.asm"

# This function needs to be called by other files, so it needs to be global
.globl pixel_update


.text
# void pixel_update(int current_frame)
#	1. This function goes through the array of pixels and finds the one that is selected (maybe you want to implement this as a different function?)
#	2. If no pixel is selected, then select pixel 0
#	3. Reads the state of the keyboard buttons and move the selected pixel accordingly
#		3.1. The pixel moves up to one pixel up/down and up to one pixel left/right according to the keyboard input.
#		3.2. The pixel must not leave the bounds of the display (check the .eqv in constants.asm)
#	4. Every 60 frames (use the input): If the user pressed the action button (B) the current selected pixel is deselected and the next pixel is selected (the array loops around).
#		You may need some variables!
pixel_update:
	enter s0, s1, s2
	# a0 is the frame counter
	move s2, a0
	
	jal pixel_find_selected
	move a0, v0
	move s1, v0
	jal pixel_get_element
	move s0, v0
	
	_up:
	lw t0, up_pressed
	beqz t0, _down
	
	# move up
	lw t1, pixel_y(s0)
	beqz t1, _down
	
	subi t1, t1, 1
	sw t1, pixel_y(s0)
	
	_down:
	lw t0, down_pressed
	beqz t0, _right
	
	# move down
	lw t1, pixel_y(s0)
	addi t1, t1, 1
	bge t1, DISPLAY_H, _right
	
	sw t1, pixel_y(s0)
	
	_right:
	lw t0, right_pressed
	beqz t0, _left
	
	# move right
	lw t1, pixel_x(s0)
	addi t1, t1, 1
	bge t1, DISPLAY_W, _left
	
	sw t1, pixel_x(s0)
	
	_left:
	lw t0, left_pressed
	beqz t0, _action
	
	# move left
	lw t1, pixel_x(s0)
	beqz t1, _action
	
	subi t1, t1, 1
	sw t1, pixel_x(s0)
	
	_action:
	
	# Check a0 (as s2) mod 60
	li t0, 60
	div s2, t0
	mfhi t2
	beqz t2, _check_press
	j _done
	
	_check_press:
	lw t0, action_pressed
	beqz t0, _done
	
	# Turn pixel off
	li t0, 0
	sw t0, pixel_selected(s0)
	
	# Get next pixel using s1 as old logical
	addi s1, s1, 1
	beq s1, n_pixels, _round
	j _set_new
	
	_round:
		li s1, 0
		
	_set_new:
	move a0, s1
	jal pixel_get_element
	li t0, 1
	sw t0, pixel_selected(v0)
	
	_done:
	
	leave s0, s1, s2

# Perhaps implement this function?
pixel_find_selected:
	enter s0
	
	# Search the elements
	li s0, 0
	_search_loop:
		beq s0, n_pixels, _not_found
		
		# Get the element
		move a0, s0
		jal pixel_get_element
		
		# Check whether selected
		lw t0, pixel_selected(v0)
		beq t0, 1, _found
		
		addi s0, s0, 1
		j _search_loop
	_not_found:
		li a0, 0
		jal pixel_get_element
		li t0, 1
		sw t0, pixel_selected(v0)
		li s0, 0
	_found:
	move v0, s0
	# v0 is the logical

	leave s0
