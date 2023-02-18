#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include <stdint.h>
#include <stdbool.h>

// RISCV32I

void r_add(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_sub(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_sll(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_slt(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_sltu(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_xor(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_srl(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_sra(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_or(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_and(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_lui(uint64_t* rd, uint64_t imm);
void r_auipc(uint64_t* rd, uint64_t pc, uint64_t imm);
void r_addi(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_slti(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_sltiu(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_xori(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_ori(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_andi(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_slli(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_srli(uint64_t* rd, uint64_t rs1, uint64_t imm);
void r_srai(uint64_t* rd, uint64_t rs1, uint64_t imm);

// RISCV32M

void r_mul(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_mulh(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_mulhsu(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_mulhu(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_div(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_divu(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_rem(uint64_t* rd, uint64_t reg1, uint64_t reg2);
void r_remu(uint64_t* rd, uint64_t reg1, uint64_t reg2);

#endif