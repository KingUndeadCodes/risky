    .text
    .option nopic
    .align  1
    .globl  _start
    .type   _start, @function

_start:
    li x18, 12
    li x19, 6
    add x20, x18, x19
    sub x21, x18, x19
    mul x22, x18, x19
    div x23, x18, x19
    .ident "KingUndeadCodes / RISC-V test"
