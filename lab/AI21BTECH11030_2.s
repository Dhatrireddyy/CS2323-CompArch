.data
#if needed, else ignore the data section

.text
#code starts here

#For the given example
#li x4, 0x00000000FCD18613

andi x8, x4, 0x7F

#Initialising x10 to 0

li x5, 0b0110011
beq x8, x5, r_type

li x5, 0b0010011
beq x8, x5, i_type
li x5, 0b0000011
beq x8, x5, i_type
li x5, 0b1110011
beq x8, x5, i_type
li x5, 0b1100111
beq x8, x5, i_type

li x5, 0b1100011
beq x8, x5, b_type

li x5, 0b0100011
beq x8, x5, s_type

li x5, 0b01101111
beq x8, x5, j_type
    
li x5, 0b0110111
beq x8, x5, u_type
li x5, 0b0010111
beq x8, x5, u_type

r_type:
    addi x10, x0, 1
    beq x0, x0, exit

i_type:
    addi x10, x0, 2
    beq x0, x0, exit

b_type:
    addi x10, x0, 3
    beq x0, x0, exit
    
s_type:
    addi x10, x0, 4
    beq x0, x0, exit

j_type:
    addi x10, x0, 5
    beq x0, x0, exit
    
u_type:
    addi x10, x0, 6
    beq x0, x0, exit
    
exit:
    add x0, x0, x0
    
#The final result should be in register x10

    
    
    
