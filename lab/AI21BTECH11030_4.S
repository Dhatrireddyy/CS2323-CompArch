#AI21BTECH11030 - VELMA DHATRI REDDY
#AI21BTECH10016 - BLESSY ANVITHA J

.section .data
L1: .word 10000000

.section .text
.global main

main:
    la x3, L1

    lui x4, 0x10012

    addi x5, x0, 0x0
    addi x6, x0, 0x20

    sw x5, 4(x4)
    sw x6, 8(x4)

Load:
     lw x10, 0(x3)

sw x6, 12(x4)

glow:
     addi x10, x10, -1
     bne x10, x0, glow

sw x5, 12(x4)
lw x11, 0(x3)

off:
    addi x11, x11, -1
     bne x11, x0, off

 beq x0, x0, Load

 Lwhile1: j Lwhile1

