.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:

    # Error checks
    li t0 1
    blt a1 t0 exception
    blt a2 t0 exception
    blt a4 t0 exception
    blt a5 t0 exception
    bne a2 a4 exception
    # Prologue
    addi sp sp -24
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s6 20(sp)
    
    mv s0 a0 # pointer to m0
    mv s1 a1 # row of m0
    mv s2 a3 # pointer to m1
    mv s3 a5 # colomn of m1
    mv s4 a6 # pointer to result
    mv s6 a5

outer_loop_start:
    beq s1 x0 end
inner_loop_start:
    beq s3 x0 outer_loop_end
    
    addi sp sp -28
    sw a0 0(sp)
    sw a1 4(sp)
    sw a2 8(sp)
    sw a3 12(sp)
    sw a4 16(sp)
    sw a5 20(sp)
    sw ra 24(sp)
    
    # a0
    sub t1 a1 s1 # current row
    mul t1 t1 a2  # row start index
    slli t1 t1 2 # row offset
    add a0 s0 t1 # start address of m0
    # a1
    sub t1 a5 s3 # current col start index
    slli t1 t1 2 # col offset
    add a1 s2 t1 # start address of m1
    # a2
    # a3
    li a3 1
    # a4
    mv a4 s6
    # calling function
    jal ra dot
    # store result
#     slli t4 s5 2
#     add s4 s4 t4
    sw a0 0(s4)
inner_loop_end:
    lw a0 0(sp)
    lw a1 4(sp)
    lw a2 8(sp)
    lw a3 12(sp)
    lw a4 16(sp)
    lw a5 20(sp)
    lw ra 24(sp)
    addi sp sp 28
    addi s3 s3 -1
    addi s4 s4 4
    j inner_loop_start
outer_loop_end:
    addi s1 s1 -1
    add s3 a5 x0
    j outer_loop_start
end:
    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s6 20(sp)
    addi sp sp 24

    jr ra
exception:
    li a0 38
    j exit