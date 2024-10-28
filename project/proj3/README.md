# CS61CPU

Look ma, I made a CPU! Here's what I did:

## control logic
### PCSel: 
- 0 Selects the PC+4 input for all other instructions.
- 1 Selects the ALU input for all B-type instructions where the branch is taken (according to the branch comparator output) and all jumps.
### ImmSel
- 000 = I (000 = 0b000)
- 001 = S
- 010 = B
- 011 = U
- 100 = J
### RegWEn
- 1 if the instruction writes to a register
- 0 otherwise
### BrUn
- 1 if the branch instruction is unsigned
- 0 if the branch instruction is signed
- Don't care for all other instructions
### ASel
- 0 send the data in RegReadData1 to the ALU
- 1 send the PC to the ALU
### BSel
- 0 send the data in RegReadData2 to the ALU
- 1 send the immediate to the ALU
### ALUSel
- 0 add
- 1 sll
- 2 slt
- 4 xor
- 5 srl
- 6 or
- 7 and
- 8 mul
- 9 mulh
- 11 mulhu
- 12 sub
- 13 sra
- 15 bsel
### MemRW
- 1 if the instruction writes to memory
- 0 otherwise
### WBSel
- 10 write the memory read from DMEM to rd
- 01 write the memory read from the ALU output to rd
- 11 write the memory read from PC+4 to rd
