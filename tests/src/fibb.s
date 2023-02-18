/*
    # Register conventions
    # x1 - current
    # x2 - next
    # x3 - counter
    # x4 - temp
*/

    .text
    .option nopic
    .align  1
    .globl  _start
    .type   _start, @function

_start:

li x1, 0
li x2, 1
li x3, 10

loop:
    add x4, x1, x2
    mv x1, x2
    mv x2, x4
    addi x3, x3, -1
    bne x3, zero, loop
