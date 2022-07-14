# Multiply 2 4-bit numbers!
# a0 - input one
# a1 - input two
# v0 - return value
func:
	move t0, a0
	move t3, a1
	li t4, 0
	li t1, 1
	li t2, 4
_func_do:
	and t9, t3, t1
	beq t9, zero, _func_endif
	add t4, t4, t0
_func_endif:
	sll t0, t0, 1
	sll t1, t1, 1
	sub t2, t2, 1
	bne t2, zero, _func_do
	move v0, t4
	jr ra