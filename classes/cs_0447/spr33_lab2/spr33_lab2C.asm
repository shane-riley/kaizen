# Shane Riley (spr33)
.data
str: .asciiz "What is the first value?\n"
str2: .asciiz "What is the second value?\n"
out1: .asciiz " - "
out2: .asciiz " = "

a: .word 0
b: .word 0
c: .word 0

.text
.globl main
main:

# Query for a
la a0, str
li v0, 4
syscall

# Get a
li v0, 5
syscall
sw v0, a

# Query for b
la a0, str2
li v0, 4
syscall

# Get b
li v0, 5
syscall
sw v0, b

# Subtract a - b and store in c
lw t0, a
lw t1, b
sub t2, t0, t1
sw t2, c

# Print a
li v0, 1
lw a0, a
syscall

# Print " - "
li v0, 4
la a0, out1
syscall

# Print b
li v0, 1
lw a0, b
syscall

# Print " = "
li v0, 4
la a0, out2
syscall

# Print c
li v0, 1
lw a0, c
syscall

# Exit
li v0, 10
syscall


