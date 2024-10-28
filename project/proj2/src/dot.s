.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:

    # Prologue
    li t0 1
    blt a2 t0 number_of_elements_exception
    blt a3 t0 stride_of_either_array_exception
    blt a4 t0 stride_of_either_array_exception
    
    addi sp sp -20
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    
    mv s0 a0 # address of array0
    mv s1 a1 # address of array1
    mv s2 a2
    li t1 0 # result
    li t2 0 # index of array0
    li t3 0 # index of array1

loop_start:
    beq s2 x0 loop_end
    slli s3 t2 2
    slli s4 t3 2
    add s0 a0 s3
    add s1 a1 s4
    lw t4 0(s0)
    lw t5 0(s1)
    mul t6 t4 t5 
    add t1 t1 t6
    
    # change index and numbers
    addi s2 s2 -1
    add t2 t2 a3
    add t3 t3 a4
    j loop_start
loop_end:
    mv a0 t1
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    addi sp sp 20
    # Epilogue
    

    jr ra
number_of_elements_exception:
    li a0 36
    j exit
stride_of_either_array_exception:
    li a0 37
    j exit
    