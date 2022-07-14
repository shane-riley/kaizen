## This file implements the functions that display the pixels based on the model

# Include the macros file so that we save some typing! :)
.include "macros.asm"
# Include the constants settings file with the board settings! :)
.include "constants.asm"
# We will need to access the pixel model, include the structure offset definitions
.include "pixel_struct.asm"

# This function needs to be called by other files, so it needs to be global
.globl pixel_draw

.text
# void pixel_draw()
#	1. This function goes through the array of pixels and for each
#		1.1. Gets its (x, y) coordinates and selected status
#		1.2. Prints it in the display using function display_set_pixel (display.asm)
#			1.2.1. If the pixel is not selected, print it using some color (Not COLOR_BLACK, as this is the background color)
#			1.2.2. If the pixel is selected, print it using another color
pixel_draw:
	enter s0,s1
	
	# Init start and end
	li s0, 0
	_draw_loop:
		
		# Check for exit
		beq s0, n_pixels, _exit_draw_loop
		
		# Get the pixel using pixel_get_element
		move a0, s0
		jal pixel_get_element
		
		# Pull apart structure
		lw a0, pixel_x(v0)
		lw a1, pixel_y(v0)
		lw t2, pixel_selected(v0)
		
		beqz t2, _is_not_selected
		_is_selected:
		li a2,COLOR_MAGENTA
		
		j _display
		_is_not_selected:
		li a2,COLOR_BLUE
		
		_display:
		# Call display set pixel
		jal display_set_pixel
		
		# Iterate
		addi s0, s0, 1
		j _draw_loop
	_exit_draw_loop:

	leave s0, s1
