# Shane Riley (spr33)
.data
a: .byte 0
b: .byte 16
c: .byte 33

.text
.globl main
main:

# Perform subtraction
lb t0,b
lb t1,c
sub t2,t0,t1
sb t2,a

# Print memory address of b
li v0,1
la a0,b
syscall



