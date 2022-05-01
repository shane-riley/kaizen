.data
  returned: .asciiz "The function returned\n"
.text
.globl main

main:
  # Decode the first instruction in function "func" (addi v0, zero, 0x1337)
  la a0, func
  jal decode_instruction

  # Encode the instruction addi v0, zero, 0x1234
  li a0, 8
  li a1, 0
  li a2, 2
  li a3, 0x1234
  jal encode_instruction

  # Print string
  la a0, returned
  li v0, 4
  syscall
  # Call function
  jal func
  # Print return value
  move a0, v0
  li v0, 34
  syscall

  # Exit
  li v0, 10
  syscall

func:
	addi v0, zero, 0x1337
	jr ra

# Prints the different fields of an I-type instruction
# decode_instruction(a0: memory address of instruction)
decode_instruction:
  # Implement B.1 here
  
  lw s0, (a0)

  # Make copies
  move t0, s0
  move t1, s0
  move t2, s0
  move t3, s0

  # Shift opcode, rs, rt  
  srl t0, t0, 26
  srl t1, t1, 21
  srl t2, t2, 16

  # Apply against masks
  and t0, t0, 0x2F
  and t1, t1, 0x1F
  and t2, t2, 0x1F
  and t3, t3, 0xFFFF
  
  # Print opcode, rs, rt, immediate
  li v0, 1
  move a0, t0
  syscall
  
  li v0, 11
  li a0, 0x0a
  syscall
  
  li v0, 1
  move a0, t1
  syscall
  
  li v0, 11
  li a0, 0x0a
  syscall
  
  li v0, 1
  move a0, t2
  syscall
  
  li v0, 11
  li a0, 0x0a
  syscall
  
  li v0, 34
  move a0, t3
  syscall
  
  li v0, 11
  li a0, 0x0a
  syscall
  
  jr ra


# Encodes the fields of an I-type instruction and returns it
# encode_instruction(a0: opcode, a1: rs, a2: rt, a3: immediate)
encode_instruction:
  # Implement B.2 here
  
  # Shift pieces to right places
  sll t0, a0, 26
  sll t1, a1, 21
  sll t2, a2, 16
  move t3, a3
  
  # Combine the four pieces using or
  or t0, t0, t1
  or t0, t0, t2
  or t0, t0, t3
  
  move v0, t0
  
  # Print operation in hex
  li v0, 34
  move a0, t0
  syscall
  
  li v0, 11
  li a0, 0x0a
  syscall
  
  jr ra