### This file contains the model for the whole game

# Eqv's loaded
.include "structs.asm"
.include "constants.asm"

.data
	
	# Board -- this is mutable and holds walls
	# 2 is indestructible
	# 1 is destructible
	board: .word 	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
								0,	2,	0,	2,	1,	2,	1,	2,	1,	2,	0,
								0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,
								0,	2,	0,	0,	0,	0,	0,	0,	0,	2,	0,
								0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,
								0,	2,	0,	0,	0,	0,	0,	0,	0,	2,	0,
								0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,
								0,	2,	0,	0,	0,	0,	0,	0,	0,	2,	0,
								0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,
								0,	2,	1,	2,	1,	2,	1,	2,	1,	2,	0,
								0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
							
	# Player position (in blits)
	playerx: .word 0
	playery: .word 0
	
	# Enemy positions
	# [{x, y, active?}], 3 enemies, so 9 words
	enemies: .word 	10,	 0, 	1,
									10,	 10, 	1,
									6,	 6, 	1
									
	# Bomb
	bombx: .word 0
	bomby: .word 0
	bombIsActive: .word 0
	bombTime: .word 0
	
	# Explosion
	expx: .word 0
	expy: .word 0
	expIsActive: .word 0
	expRadius: .word 0
	
	# Blocks


.globl get_enemy_element
.globl get_board_element
.globl set_board_element
.globl is_open

.globl playerx
.globl playery

.globl bombx
.globl bomby
.globl bombIsActive
.globl bombTime

.globl expx
.globl expy
.globl expIsActive
.globl expRadius

.text

# Enemy array accessor
# a0: index
# v0: location in memory
get_enemy_element:
	push ra
	
	la t0, enemies
	mul t1, a0, enemy_size
	add v0, t1, t0
	
	pop ra
	jr ra
# end get_enemy_element


# get board element (returns value)
# a0: x
# a1: y
# v0: current value
get_board_element:

	push ra
	
	# Mult y by length and add x
	mul t0, a1, BOARD_LENGTH
	add t0, t0, a0
	
	# Add relative to absolute address
	la t1, board
	mul t0, t0, 4
	add t2, t0, t1
	lw v0, (t2)
	
	pop ra
	jr ra
# end get_board_element


# set board element
# a0: x
# a1: y
# a2: new value
set_board_element:
	push ra
	
	# Mult y by length and add x
	mul t0, a1, BOARD_LENGTH
	add t0, t0, a0
	
	# Add relative to absolute address
	la t1, board
	mul t0, t0, 4
	add t2, t0, t1
	sw a2, (t2)
	
	pop ra
	jr ra
# end set_board_element


# is open tile
# a0: x
# a1: y
# v0: isOpen
is_open:
	push ra
	
	blt a0, 0, _closed
	blt a1, 0, _closed
	bge a0, BOARD_LENGTH, _closed
	bge a1, BOARD_LENGTH, _closed
	
	# a0 is x
	# a1 is y
	jal get_board_element
	
	move t0, v0
	
	beqz t0, _open
	j _closed
	
	_open:
	li v0, 1
	j _end
	
	_closed:
	li v0, 0
	
	_end:
	pop ra
	jr ra
# end is_open
