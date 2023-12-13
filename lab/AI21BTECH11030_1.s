.data
#The following line defines the 15 values present in the memory.
# We would use different values in our evaluation and
# hence you should try various combinations of these values in your testing.
.dword 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 523, 524, 525, 533, 512
#(dword stands for doubleword)

.text
    #The following line initializes register x3 with 0x10000000 
    #so that you can use x3 for referencing various memory locations. 
    lui x3, 0x10000
    
    ld x10, 0(x3)
    ld x9, 8*1(x3)
    add x10, x10, x9
    ld x9, 8*2(x3)
    add x10, x10, x9
    ld x9, 8*3(x3)
    add x10, x10, x9
    ld x9, 8*4(x3)
    add x10, x10, x9
    ld x9, 8*5(x3)
    add x10, x10, x9
    ld x9, 8*6(x3)
    add x10, x10, x9
    ld x9, 8*7(x3)
    add x10, x10, x9
    ld x9, 8*8(x3)
    add x10, x10, x9
    ld x9, 8*9(x3)
    add x10, x10, x9
    

    ld x9, 8*10(x3)
    sub x10, x10, x9
    ld x9, 8*11(x3)
    sub x10, x10, x9
    ld x9, 8*12(x3)
    sub x10, x10, x9
    ld x9, 8*13(x3)
    sub x10, x10, x9
    ld x9, 8*14(x3)
    sub x10, x10, x9
       
    #The final result should be in register x10
