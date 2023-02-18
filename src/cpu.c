#include <stdio.h>
#include "../include/cpu.h"
#include "../include/csr.h"

// https://msyksphinz-self.github.io/riscv-isadoc/html/rvi.html#jal

void cpu_init(CPU *cpu) {
    cpu->regs[0] = 0x00;                    // Register x0 hardwired to 0
    cpu->regs[2] = DRAM_BASE + DRAM_SIZE;   // Set stack pointer
    cpu->pc = DRAM_BASE;                    // Set program counter to the base address
}

uint32_t cpu_fetch(CPU *cpu) {
    return bus_load(&(cpu->bus), cpu->pc, 32);
}

uint64_t cpu_load(CPU* cpu, uint64_t addr, uint64_t size) {
    return bus_load(&(cpu->bus), addr, size);
}

void cpu_store(CPU* cpu, uint64_t addr, uint64_t size, uint64_t value) {
    bus_store(&(cpu->bus), addr, size, value);
}

void cpu_reset(CPU* cpu) {
    for (int i = 0; i < 31; i++) cpu->regs[i] = 0x00;
}

void toString(CPU cpu) {
    puts("{");
    for (int i = 0; i < 32; i++) printf("\tx%d: \e[0;33m%lld\e[0m,\n", i, cpu.regs[i]);
    puts("\r}");
}

#define IMM_I(inst) ((int64_t)(int32_t) (inst & 0xfff00000)) >> 20
#define IMM_S(inst) ((int64_t)(int32_t)(inst & 0xfe000000) >> 20) | ((inst >> 7) & 0x1f)
#define IMM_J(inst) (uint64_t)((int64_t)(int32_t)(inst & 0x80000000) >> 11) | (inst & 0xff000) | ((inst >> 9) & 0x800) | ((inst >> 20) & 0x7fe)
#define IMM_B(inst) ((int64_t)(int32_t)(inst & 0x80000000) >> 19) | ((inst & 0x80) << 4) | ((inst >> 20) & 0x7e0) | ((inst >> 7) & 0x1e); // imm[4:1]

void cpu_debug_log(uint32_t inst) {
    const uint32_t opcode = inst & 0x7f;
    const uint32_t funct3 = (inst >> 12) & 0x7;
    const uint32_t funct7 = (inst >> 25) & 0x7f;
    const uint64_t imm_i  = IMM_I(inst);
    switch (opcode) {
        // Add more things here :<
        case 0b0110111: printf("[\e[34mDEBUG\e[0m] \e[91mlui\e[0m \e[34mx%d\e[0m, \e[93m%lld\e[0m\n", (inst >> 7) & 0x1f, (uint64_t)(int64_t)(int32_t)(inst & 0xfffff000) >> 12); break;
        case 0b0110011: {
            switch (funct3) {
                case 0: (funct7 == 32) ? printf("[\e[34mDEBUG\e[0m] \e[91msub\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f) : printf("[\e[34mDEBUG\e[0m] \e[91madd\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
                case 1: printf("[\e[34mDEBUG\e[0m] \e[91msll\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
                case 2: printf("[\e[34mDEBUG\e[0m] \e[91mslt\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
                case 3: printf("[\e[34mDEBUG\e[0m] \e[91msltu\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
                case 4: printf("[\e[34mDEBUG\e[0m] \e[91mxor\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
                case 5: (funct7 == 32) ? printf("[\e[34mDEBUG\e[0m] \e[91msrl\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f) : printf("[\e[34mDEBUG\e[0m] \e[91msra\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
                case 6: printf("[\e[34mDEBUG\e[0m] \e[91mor\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
                case 7: printf("[\e[34mDEBUG\e[0m] \e[91mand\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93mx%d\e[0m\n", (inst >> 7) & 0x1f, (inst >> 15) & 0x1f, (inst >> 20) & 0x1f); break;
            }
            break;
        }
        case 0b0010011: {
            switch (funct3) {
                case 0: printf("[\e[34mDEBUG\e[0m] \e[91maddi\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93m%lld\e[0m\n", ((inst >> 7) & 0x1f), ((inst >> 15) & 0x1f), IMM_I(inst)); break;
                case 1: printf("[\e[34mDEBUG\e[0m] \e[91mslli\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93m%lld\e[0m\n", ((inst >> 7) & 0x1f), ((inst >> 15) & 0x1f), IMM_I(inst)); break;
                case 2: printf("[\e[34mDEBUG\e[0m] \e[91mslti\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93m%lld\e[0m\n", ((inst >> 7) & 0x1f), ((inst >> 15) & 0x1f), IMM_I(inst)); break;
                case 3: printf("[\e[34mDEBUG\e[0m] \e[91msltiu\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93m%lld\e[0m\n", ((inst >> 7) & 0x1f), ((inst >> 15) & 0x1f), IMM_I(inst)); break;
                case 4: printf("[\e[34mDEBUG\e[0m] \e[91mxori\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93m%lld\e[0m\n", ((inst >> 7) & 0x1f), ((inst >> 15) & 0x1f), IMM_I(inst)); break;
                // NOTE: Add 5
                case 6: printf("[\e[34mDEBUG\e[0m] \e[91mori\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93m%lld\e[0m\n", ((inst >> 7) & 0x1f), ((inst >> 15) & 0x1f), IMM_I(inst)); break;
                case 7: printf("[\e[34mDEBUG\e[0m] \e[91mandi\e[0m \e[34mx%d\e[0m, \e[93mx%d\e[0m, \e[93m%lld\e[0m\n", ((inst >> 7) & 0x1f), ((inst >> 15) & 0x1f), IMM_I(inst)); break;
            }
            break;
        }
    }
}

int cpu_exec(CPU* cpu, uint32_t inst) {
    const uint32_t opcode = inst & 0x7f;
    const uint32_t funct3 = (inst >> 12) & 0x7;
    const uint32_t funct7 = (inst >> 25) & 0x7f;
    cpu->regs[0] = 0x00;
    cpu_debug_log(inst);
    switch (opcode) {
        case 0b0001111: printf("[\e[1;33mWARNING\e[0m] Fence NOT YET supported.\n"); break;
        case 0b0110111: r_lui(&cpu->regs[(inst >> 7) & 0x1f], (uint64_t)(int64_t)(int32_t)(inst & 0xfffff000)); break;
        case 0b0010111: r_auipc(&cpu->regs[(inst >> 7) & 0x1f], cpu->pc, IMM_I(inst)); break;
        case 0b1101111: {
            uint64_t imm = IMM_J(inst);
            cpu->regs[(inst >> 7)  & 0x1f] = cpu->pc + 4;
            cpu->pc = cpu->pc + (int64_t) imm - 4;
            break;
        }
        case 0b1100011: {
            const uint64_t BRANCH_IMMI = IMM_B(inst);
            const uint64_t NEW_PC = cpu->pc + (int64_t)BRANCH_IMMI - 4;
            switch (funct3) {
                case 0: ((int64_t)cpu->regs[(inst >> 15) & 0x1f] == (int64_t)cpu->regs[(inst >> 20)]) ? cpu->pc = NEW_PC : 0; break;
                case 1: ((int64_t)cpu->regs[(inst >> 15) & 0x1f] != (int64_t)cpu->regs[(inst >> 20)]) ? cpu->pc = NEW_PC : 0; break;
                case 2: ((int64_t)cpu->regs[(inst >> 15) & 0x1f] < (int64_t)cpu->regs[(inst >> 20)]) ? cpu->pc = NEW_PC : 0; break;
                case 3: ((int64_t)cpu->regs[(inst >> 15) & 0x1f] >= (int64_t)cpu->regs[(inst >> 20)]) ? cpu->pc = NEW_PC : 0; break;
                case 4: (cpu->regs[(inst >> 15) & 0x1f] < cpu->regs[(inst >> 20)]) ? cpu->pc = NEW_PC : 0; break;
                case 5: (cpu->regs[(inst >> 15) & 0x1f] >= cpu->regs[(inst >> 20)]) ? cpu->pc = NEW_PC : 0; break;
            }
            break;
        }
        case 0b1110011: {
            const uint32_t csr = ((inst & 0xfff00000) >> 20);
            switch (funct3) {
                case 0: break; // NOTE: Error Instructions
                case 1: cpu->regs[(inst >> 7) & 0x1f] = csr_read(cpu, csr); csr_write(cpu, csr, cpu->regs[(inst >> 15) & 0x1f]); break;
                case 2: csr_write(cpu, csr, cpu->csrs[csr] | cpu->regs[(inst >> 7) & 0x1f]); break;
                case 3: csr_write(cpu, csr, cpu->csrs[csr] & !(cpu->regs[(inst >> 7) & 0x1f])); break;
                case 4: csr_write(cpu, csr, cpu->regs[(inst >> 15) & 0x1f]); break;
                case 5: csr_write(cpu, csr, cpu->csrs[csr] | cpu->regs[(inst >> 7) & 0x1f]); break;
                case 6: csr_write(cpu, csr, cpu->csrs[csr] & !cpu->regs[(inst >> 7) & 0x1f]); break;
            }
            break;
        }
        case 0b0100011: {
            uint64_t imm_s = IMM_S(inst);
            uint64_t addr = cpu->regs[(inst >> 15) & 0x1f] + (int64_t)imm_s;
            switch (funct3) {
                case 0: cpu_store(cpu, addr, 8, cpu->regs[(inst >> 20) & 0x1f]); break;
                case 1: cpu_store(cpu, addr, 16, cpu->regs[(inst >> 20) & 0x1f]); break;
                case 2: cpu_store(cpu, addr, 32, cpu->regs[(inst >> 20) & 0x1f]); break;
                case 3: cpu_store(cpu, addr, 64, cpu->regs[(inst >> 20) & 0x1f]); break; // NOTE: RV64I ISA
            }
            break;
        }
        case 0b0000011: {
            uint64_t imm = IMM_I(inst);
            uint64_t addr = cpu->regs[(inst >> 15) & 0x1f] + (int64_t)imm;
            switch (funct3) {
                case 0: cpu->regs[(inst >> 7) & 0x1f] = (int64_t)(int8_t)cpu_load(cpu, addr, 8); break;
                case 1: cpu->regs[(inst >> 7) & 0x1f] = (int64_t)(int16_t)cpu_load(cpu, addr, 16); break;
                case 2: cpu->regs[(inst >> 7) & 0x1f] = (int64_t)(int32_t)cpu_load(cpu, addr, 32); break;
                case 3: cpu->regs[(inst >> 7) & 0x1f] = (int64_t)cpu_load(cpu, addr, 64); break;
                case 4: cpu->regs[(inst >> 7) & 0x1f] = cpu_load(cpu, addr, 8); break;
                case 5: cpu->regs[(inst >> 7) & 0x1f] = cpu_load(cpu, addr, 16); break;
            }
            break;
        }
        case 0b0010011: {
            switch (funct3) {
                case 0: r_addi(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
                case 1: r_slli(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
                case 2: r_slti(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
                case 3: r_sltiu(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
                case 4: r_xori(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
                case 5: (funct7 == 32) ? r_srai(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)) : r_srli(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
                case 6: r_ori(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
                case 7: r_andi(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], IMM_I(inst)); break;
            }
            break;
        }
        case 0b0110011: {
            switch (funct3) {
                case 0: (funct7 == 1) ? r_mul(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : (funct7 == 32) ? r_sub(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_add(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
                case 1: (funct7 == 1) ? r_mulh(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_sll(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
                case 2: (funct7 == 1) ? r_mulhsu(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_slt(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
                case 3: (funct7 == 1) ? r_mulhu(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_sltu(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
                case 4: (funct7 == 1) ? r_div(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_xor(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
                case 5: (funct7 == 1) ? r_divu(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : (funct7 == 32) ? r_srl(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_sra(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
                case 6: (funct7 == 1) ? r_rem(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_or(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
                case 7: (funct7 == 1) ? r_remu(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]) : r_and(&cpu->regs[(inst >> 7) & 0x1f], cpu->regs[(inst >> 15) & 0x1f], cpu->regs[(inst >> 20) & 0x1f]); break;
            };
            break;
        }
        case 0b0000000: break;
        default: {
            if (opcode == 0x20) return 0; // END OF PROGRAM
            printf("[\e[91mERROR\e[0m] Unknown Instruction: (0x%X)<func7=%d,func3=%d,opcode=%d>\n", inst, funct7, funct3, opcode);
            return 0;
        }
    }
    return 1;
}