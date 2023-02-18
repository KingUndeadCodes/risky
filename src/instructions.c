#include "../include/instructions.h"

/// @brief Adds the registers rs1 and rs2 and stores the result in rd.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_add(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 + reg2;
}

/// @brief Subs the register rs2 from rs1 and stores the result in rd.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_sub(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 - reg2;
}

/// @brief Performs logical left shift on the value in register rs1 by the shift amount held in the lower 5 bits of register rs2.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_sll(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 << reg2;
}

/// @brief Place the value 1 in register rd if register rs1 is less than register rs2 when both are treated as signed numbers, else 0 is written to rd.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_slt(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = (signed)reg1 < (signed)reg2 ? 1 : 0; 
}

/// @brief Place the value 1 in register rd if register rs1 is less than register rs2 when both are treated as unsigned numbers, else 0 is written to rd.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_sltu(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = (unsigned)reg1 < (unsigned)reg2 ? 1 : 0; 
}

/// @brief Performs bitwise XOR on registers rs1 and rs2 and place the result in rd.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_xor(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 ^ reg2;
}

/// @brief Logical right shift on the value in register rs1 by the shift amount held in the lower 5 bits of register rs2.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_srl(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 >> (unsigned)reg2;
}

/// @brief Performs arithmetic right shift on the value in register rs1 by the shift amount held in the lower 5 bits of register rs2.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_sra(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 >> (signed)reg2;
}

/// @brief Performs bitwise OR on registers rs1 and rs2 and place the result in rd.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_or(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 | reg2;
}

/// @brief Performs bitwise AND on registers rs1 and rs2 and place the result in rd.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_and(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 & reg2;
}

/// @brief Build 32-bit constants and uses the U-type format. LUI places the U-immediate value in the top 20 bits of the destination register rd, filling in the lowest 12 bits with zeros.
/// @param rd Result Reigster
/// @param imm Immediate (func7)
void r_lui(uint64_t* rd, uint64_t imm) {
    *rd = imm << 12;
}

/// @brief Build pc-relative addresses and uses the U-type format. AUIPC forms a 32-bit offset from the 20-bit U-immediate, filling in the lowest 12 bits with zeros, adds this offset to the pc, then places the result in register rd.
/// @param rd Result Reigster
/// @param imm Immediate (func7)
void r_auipc(uint64_t* rd, uint64_t pc, uint64_t imm) {
    *rd = pc + (imm << 12);
}

/// @brief Adds the sign-extended 12-bit immediate to register rs1. Arithmetic overflow is ignored and the result is simply the low XLEN bits of the result. ADDI rd, rs1, 0 is used to implement the MV rd, rs1 assembler pseudo-instruction.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_addi(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = rs1 + imm;
}

/// @brief Place the value 1 in register rd if register rs1 is less than the signextended immediate when both are treated as signed numbers, else 0 is written to rd.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_slti(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = (rs1 < (int64_t)imm) ? 1 : 0;
}

/// @brief Place the value 1 in register rd if register rs1 is less than the immediate when both are treated as unsigned numbers, else 0 is written to rd.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_sltiu(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = (rs1 < imm) ? 1 : 0;
}

/// @brief Performs bitwise XOR on register rs1 and the sign-extended 12-bit immediate and place the result in rd.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_xori(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = rs1 ^ imm;
}

/// @brief Performs bitwise OR on register rs1 and the sign-extended 12-bit immediate and place the result in rd.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_ori(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = rs1 | imm;
}

/// @brief Performs bitwise AND on register rs1 and the sign-extended 12-bit immediate and place the result in rd.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_andi(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = rs1 & imm;
}

/// @brief Performs logical left shift on the value in register rs1 by the shift amount held in the lower 5 bits of the immediate.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_slli(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = rs1 << (uint32_t) (imm & 0x1f);
}

/// @brief Performs logical right shift on the value in register rs1 by the shift amount held in the lower 5 bits of the immediate.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_srli(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = rs1 >> imm;
}

/// @brief Performs arithmetic right shift on the value in register rs1 by the shift amount held in the lower 5 bits of the immediate.
/// @param rd Result Reigster
/// @param rs1 Register 1
/// @param imm Immediate (func7)
void r_srai(uint64_t* rd, uint64_t rs1, uint64_t imm) {
    *rd = (int32_t)rs1 >> imm;
}

/// @brief Performs an XLEN-bit * XLEN-bit multiplication of signed rs1 by signed rs2 and places the lower XLEN bits in the destination register.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_mul(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 * reg2;
}

/// @brief Performs an XLEN-bit * XLEN-bit multiplication of signed rs1 by signed rs2 and places the upper XLEN bits in the destination register.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_mulh(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = ((int64_t)reg1 * (int64_t)reg2) >> 32;
}

/// @brief Performs an XLEN-bit * XLEN-bit multiplication of unsigned rs1 by unsigned rs2 and places the upper XLEN bits in the destination register.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_mulhsu(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd =  ((int64_t)reg1 * (int64_t)reg2) >> 32;
}

/// @brief Performs an XLEN-bit * XLEN-bit multiplication of unsigned rs1 by unsigned rs2 and places the upper XLEN bits in the destination register.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_mulhu(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd =  ((int64_t)reg1 * (int64_t)reg2) >> 32;
}

/// @brief Perform an XLEN bits by XLEN bits signed integer division of rs1 by rs2, rounding towards zero.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_div(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 / (signed)reg2;
}

/// @brief Perform an XLEN bits by XLEN bits unsigned integer division of rs1 by rs2, rounding towards zero.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_divu(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 / (unsigned)reg2;
}

/// @brief Perform an XLEN bits by XLEN bits signed integer reminder of rs1 by rs2.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_rem(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 % (signed)reg2;
}

/// @brief Perform an XLEN bits by XLEN bits unsigned integer reminder of rs1 by rs2.
/// @param rd Result Reigster
/// @param reg1 Register 1
/// @param reg2 Register 2
void r_remu(uint64_t* rd, uint64_t reg1, uint64_t reg2) {
    *rd = reg1 % (unsigned)reg2;
}