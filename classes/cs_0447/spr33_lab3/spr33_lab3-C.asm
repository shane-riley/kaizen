.data
  myArray: .word 0, 4, -3, 5, 2, 1, -6, 15, -8, 10
  
  # Declare your variables here
  # // add your code //
  str1: .asciiz "What is the first index?\n"
  str2: .asciiz "What is the second index?\n"
  str3: .asciiz "Your value sum is: "
  firstIndex: .word 0
  secondIndex: .word 0
  
  firstValue: .word 0
  secondValue: .word 0
  sum: .word 0

.text
.globl main
main:
  # Ask for two indices
  # Make it friendly!! Print out a prompt so people know what to do! :)
  # // add your code //
  
  # Query for firstIndex
  la a0, str1
  li v0, 4
  syscall

  # Get firstIndex
  li v0, 5
  syscall
  sw v0, firstIndex
  
  # Query for secondIndex
  la a0, str2
  li v0, 4
  syscall

  # Get secondIndex
  li v0, 5
  syscall
  sw v0, secondIndex

  # Write your code here to retrieve each value from the array and sum them
  # // add your code //
  
  # Get first value
  la t0, myArray
  li t1, 4
  lw t2, firstIndex
  mul t4, t1, t2  # Find first array shift
  add t5, t4, t0  # Find address of word in array
  lw t6, 0(t5)  # Pull value out of memory
  sw t6, firstValue  # Store value
  
  # Get second value
  lw t2, secondIndex
  mul t4, t1, t2  # Find first array shift
  add t5, t4, t0  # Find address of word in array
  lw t6, 0(t5)  # Pull value out of memory
  sw t6, secondValue  # Store value
  
  # Add the values
  lw t0, firstValue
  lw t1, secondValue
  add t2, t0, t1
  sw t2, sum
  
  # Print the result
  # // add your code //
  
  # Query for firstIndex
  la a0, str3
  li v0, 4
  syscall
  lw a0, sum
  li v0, 1
  syscall

  # Exit the program with the exit syscall
  li  v0, 10
  syscall