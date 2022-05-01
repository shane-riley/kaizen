.data
	# Variables
	
	coldString: 		.asciiz "You're cold.\n"
	warmString: 		.asciiz "You're warm!\n"
	highString: 		.asciiz "Your guess is too high.\n"
	lowString: 			.asciiz "Your guess is too low.\n"
	promptString: 	.asciiz "Enter a number between 0 and 99: "
	loseString: 		.asciiz "You lose. The number was: "
	winString: 			.asciiz "Congratulations! You win!\n"
	
	correctAnswer: .word 0
	yourAnswer: .word 0
	maxNumGuesses: .word 5
	warmDifference: .word 10
	lowerThreshold: .word 0
	higherThreshold: .word 0

.text
.globl main

main:
	
	# Pick the correct answer
	jal rand
	sw v0, correctAnswer
	
	# Set threshold
	lw t0, correctAnswer
	li t1, 9
	add t2, t0, t1
	sub t3, t0, t1
	sw t2, higherThreshold
	sw t3, lowerThreshold
	
	# Run the game (return is the outcome)
	jal runGame
	
	# If 1 win, else loss
	li t0, 1
	beq v0, 1, win
	j loss
	
# end main

rand:
	
	push ra
	
	li a0, 0
	li a1, 99
	li v0, 42
	syscall
	
	pop ra
	jr ra

# end rand

runGame:

	push ra
	
	# Guess counter
	li s0, 1
	
	_gameLoop:
		
		# Check counter
		lw t0, maxNumGuesses
		bgt s0, t0, _loseGame
		
		# Query for answer
		jal prompt
		
		# Check win
		lw t0, yourAnswer
		lw t1, correctAnswer
		beq t0, t1, _winGame
		
		# Give feedback
		jal feedback
		
		# Iterate guesses
		add s0, s0, 1
		
		j _gameLoop
	# end _gameLoop
	
	_winGame:
		li v0, 1
		pop ra
		jr ra
		
	_loseGame:
		li v0, 0
		pop ra
		jr ra

# end runGame

prompt:
	
	push ra
	
	la a0, promptString
	li v0, 4
	syscall
	
	li v0, 5
	syscall
	sw v0, yourAnswer
	
	pop ra
	jr ra

# end prompt

win:
	
	# Print string
	la a0, winString
	li v0, 4
	syscall
	
	j end
	
# end win

loss:

	# Print string
	la a0, loseString
	li v0, 4
	syscall
	
	# Print correct answer
	lw a0, correctAnswer
	li v0, 1
	syscall
	
	j end

# end _oss

end:

	# End program
	li v0, 10
	syscall

# end end

feedback:

	push ra
	
	lw t0, correctAnswer
	lw t1, yourAnswer
	
	bgt t1, t0, _high
	j _low
	
	_high:
		
		# Print
		la a0, highString
		li v0, 4
		syscall
		
		j _warmOrCold
		
	_low:
	
		# Print
		la a0, lowString
		li v0, 4
		syscall
		
		j _warmOrCold
	
	_warmOrCold:
	
	lw t2, higherThreshold
	lw t3, lowerThreshold
	
	bgt t1, t2, _cold
	blt t1, t3, _cold
	j _warm
	
	_warm:
	
		# Print
		la a0, warmString
		li v0, 4
		syscall
		
		j _endFeedback
		
	_cold:
	
		# Print
		la a0, coldString
		li v0, 4
		syscall
		
		j _endFeedback
		
	_endFeedback:
		
		pop ra
		jr ra

# end feedback

