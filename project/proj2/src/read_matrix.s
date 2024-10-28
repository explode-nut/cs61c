.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

    # Prologue
    addi sp sp -28
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw ra 24(sp)
    
    li s3 4
    li s0 -1
    mv s1 a1
    mv s2 a2
    
    li a1 0
    jal ra fopen
    beq a0 s0 fopen_exception
    mv s4 a0
    
    mv a1 s1
    li a2 4
    jal ra fread
    bne a0 s3 fread_exception

    mv a0 s4
    mv a1 s2
    li a2 4
    jal ra fread
    bne a0 s3 fread_exception
    
    lw t2 0(s1)
    lw t3 0(s2)
    mul t4 t2 t3
    slli t4 t4 2
    mv a0 t4
    jal ra malloc
    beq a0 x0 malloc_exception
    mv s5 a0
    
    mv a1 s5
    lw t2 0(s1)
    lw t3 0(s2)
    mul t4 t2 t3
    slli t4 t4 2
    mv a2 t4
    mv a0 s4
    jal ra fread
    lw t2 0(s1)
    lw t3 0(s2)
    mul t4 t2 t3
    slli t4 t4 2
    bne a0 t4 fread_exception

    mv a0 s4
    jal ra fclose
    bnez a0 fclose_exception
    mv a0 s5

    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw ra 24(sp)
    addi sp sp 28


    jr ra
malloc_exception:
    li a0 26
    j exit
fopen_exception:
    li a0 27
    j exit
fclose_exception:
    li a0 28
    j exit
fread_exception:
    li a0 29
    j exit