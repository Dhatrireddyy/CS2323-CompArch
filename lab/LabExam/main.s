.data
.dword 3 23, 46, 22, 33, 46, 78

.text
    
lui x3, 0x10000

li x10, 0x10000000

ld x5, 0(x3)

iter:  
    beq x5, x0, Exit   
    addi x5, x5, -1
    
    addi x3, x3, 8  
    ld x6, 0(x3)
    
    addi x3, x3, 8 
    ld x7, 0(x3)

    check:
        beq x6, x7, iter
        bne x6, x7, loop

    loop:
        bge x6, x7, Else
        sub x7, x7, x6
        beq x0, x0, check

    Else:
        sub x6, x6, x7
        beq x0, x0, check
        
    
    addi x10, x10, 0x100
    sd x6, 0(x10)
    beq x0, x0, iter
      
Exit: add x0, x0, x0
    

