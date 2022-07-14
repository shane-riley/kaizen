Name: Shane Riley
Username: spr33
Email: shane.riley@pitt.edu

All test cases passing:

Control signals:
- doWReg: do we write to a register?
- doWMem: do we write to memory?
- doPut: do we put RegA to the display?
- doHalt: Are we halting right now?
- isOn: Have we not halted yet?
- doSignExtend: Are we using sign-extend (or zero-extend) for the imm?
- doJumpToImm: Is PC changing to the immediate?
- doJumpToImm: Is PC changing to the rs contents?
- aluImm: Is the ALU getting an immediate (or a second register)?
- PC: current program counter
- PC' next program counter
- ARegData: Data in rs
- BRegData: Data in rt
- ARegAdd: rs
- BRegAdd: rt
- 8imm: 8 bit immediate
- 16imm: extended immediate
- subOp: (self-explanatory)
- Opcode: (self-explanatory)

REGIO:
REGIO serves as a traffic cop, determining which piece of data (immediate, PC, register value, etc.)
should be written to the register. It uses opcode and subop to do this

NextLine:
NextLine determines what the pc should be on the next cycle (+1, or jump to imm or $rs).

Controller:
This turns the opcode and subop into a set of flags, explained above

ALUController:
The ALUController turns the opcode and subop into the ALUop

