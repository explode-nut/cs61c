.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue
    addi t0 x0 1
    addi t2 x0 4
    blt a1 t0 exception_exit
    
    addi sp sp -12
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    
    add s0 a0 x0 # the pointer to the array
    add s1 a1 x0 # the # of elements in the array
    add s2 x0 x0 # the index to the array

loop_start:
    beq s1 x0 loop_end
    mul t1 s2 t2 # offset
    add s0 a0 t1 # true address 
    lw t1 0(s0)
    bge t1 x0 loop_continue
    sw x0 0(s0)
loop_continue:
    addi s2 s2 1
    sub s1 s1 t0
    j loop_start
loop_end:
    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    addi sp sp 12

    jr ra

exception_exit:
    li a0 36
    j exit