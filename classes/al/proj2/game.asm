.include "constants.asm"
.include "macros.asm"

.globl game
.text

game:
	enter
	
_welcome_loop:

	jal	handle_input
	
	# Write welcome
	li	a0, 1
	li	a1, 5
	lstr a2, "Welcome to"
	jal	display_draw_text
	li	a0, 1
	li	a1, 11
	lstr a2, "My game!"
	jal	display_draw_text
	li	a0, 1
	li	a1, 17
	lstr a2, "Press C to"
	jal	display_draw_text
	li	a0, 1
	li	a1, 23
	lstr a2, "Start"
	jal	display_draw_text
	
	# Must update the frame and wait
	jal	display_update_and_clear
	jal	wait_for_next_frame
	
	# Start if c was pressed
	lw	t0, c_pressed
	beq	t0, 1, _game_mainloop
	
	j _welcome_loop

_game_mainloop:

	# Check keyboard
	jal	handle_input
	
	# Model update (1 is win, 2 is loss, 0 is continue)
	jal update_game
	beq v0, 1, _game_win_loop
	beq v0, 2, _game_loss_loop
	
	# Display
	jal display_game
	
	# Must update the frame and wait
	jal	display_update_and_clear
	jal	wait_for_next_frame

	j	_game_mainloop
	
_game_loss_loop:
	
	jal	handle_input
	
	# Leave if x was pressed
	lw	t0, x_pressed
	bnez	t0, _game_end
	
	li	a0, 5
	li	a1, 5
	lstr	a2, "You Lose!"
	jal	display_draw_text

	li	a0, 11
	li	a1, 11
	lstr	a2, "Press x"
	jal	display_draw_text
	
	li	a0, 17
	li	a1, 17
	lstr	a2, "To exit"
	jal	display_draw_text
	
	jal	display_update_and_clear
	jal	wait_for_next_frame
	
	j _game_loss_loop

_game_win_loop:
	
	jal	handle_input
	
	# Leave if x was pressed
	lw	t0, x_pressed
	bnez	t0, _game_end
	
	li	a0, 5
	li	a1, 5
	lstr	a2, "You Win!"
	jal	display_draw_text

	li	a0, 11
	li	a1, 11
	lstr	a2, "Press x"
	jal	display_draw_text
	
	li	a0, 17
	li	a1, 17
	lstr	a2, "To exit"
	jal	display_draw_text
	
	jal	display_update_and_clear
	jal	wait_for_next_frame
	
	j _game_win_loop

_game_end:
	# Clear the screen
	jal	display_update_and_clear
	jal	wait_for_next_frame

	leave
