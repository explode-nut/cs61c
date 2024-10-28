# test i type instruction
# addi test
addi t0, x0, 3
addi t0, x0, -2
# srai test
srai t1, t0, 1
addi t0, x0, 5
srai t1, t0, 2
# andi ori xori test
addi t0, x0, 27
andi t1, t0, 3
ori t1, t0, 4
xori t1, t0, 5
# slli test
slli t1, t0, 3
# srli test
srli t1, t0, 2
addi t0, x0, -7
srli t1, t0, 3
# slti test
slti t1, t0, 3
slti t1, t0, -3
slti t1, t0, -9
addi t0, x0, 9
slti t1, t0, 3
slti t1, t0, 12

# test r type instruction
# add test
addi s0, x0, -13
addi s1, x0, 2043
addi s2, x0, 23
addi t0, x0, -15
addi t2, x0, 3
add t1, t0, t2
addi t0, x0, 15
addi t2, x0, 3
add t1, t0, t2
# sra test
sra t1, t0, t2
sra t1, s0, t2
# and or xor test
and t1, t0, t2
or t1, t0, t2
xor t1, t0, t2
# sll test
sll t1, t0, t2
# srl test
srl t1, t0, t2
srl t1, s0, t2
# slt test
slt t1, t0, t2
slt t1, t2, t0
slt t1, s0, t0
slt t1, t0, s0
# sub test
sub t1, t2, t0
sub t1, s0, t2
sub t1, t0, s0
# mul test
mul t1, t0, t2
mul t1, t0, s0
mul t1, s1, s2
mul t1, s1, s0
# mulh test
mul t1, t0, t2
mul t1, t0, s0
mul t1, s1, s2
mul t1, s1, s0
# mulhu test
mul t1, t0, t2
mul t1, t0, s0
mul t1, s1, s2
mul t1, s1, s0
