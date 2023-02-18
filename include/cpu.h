#ifndef __CPU_H
#define __CPU_H

#include <stdint.h>
#include "bus.h"
#include "instructions.h"

typedef struct CPU {
    uint64_t regs[32];                      // 32 64-bit registers (x0-x31)
    uint64_t pc;                            // 64-bit Program Counter
    uint64_t csrs[4096];                    // Control and Status Registers
    BUS bus; 
} CPU;

void cpu_init(CPU *cpu);
uint32_t cpu_fetch(CPU *cpu);
int cpu_exec(CPU *cpu, uint32_t inst);
void toString(CPU cpu); 

#endif