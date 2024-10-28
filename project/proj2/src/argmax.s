.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    li t0 1
    blt a1 t0 exception_exit
    addi sp sp -8
    sw s0 0(sp)
    sw s1 4(sp)
    li t0 0 # index
    li t1 0 # result index
    li t2 0 # max number
    mv s0 a0 # address
    mv s1 a1 # numbers

loop_start:
    beq s1 x0 loop_end
    slli t3 t0 2 # index * 4
    add s0 a0 t3
    lw t4 0(s0) # number
    bge t2 t4 loop_continue
    # t4 > t2
    mv t2 t4
    mv t1 t0
loop_continue:
    addi s1 s1 -1 # numbers - 1
    addi t0 t0 1 # index + 1
    j loop_start

loop_end:
    mv a0 t1
    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    addi sp sp 8

    jr ra
exception_exit:
    li a0 36
    j exit