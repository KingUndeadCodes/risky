#include <inttypes.h>
#include <string.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/cpu.h"

#define test(test, got, expected) printf("[\e[34mTEST\e[0m] \e[1;36m#%d\e[0m: %s\n", test, got == expected ? "\e[32mpass\e[0m" : "false");

void read_file(CPU* cpu, const char* fname) {
    uint8_t* script = 0;
    FILE *fp = fopen(fname, "rb");
    fseek(fp, 0, SEEK_END);
    unsigned long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    script = (uint8_t*)malloc(len + 1);
    if (script) fread(script, len, 1, fp);
    fclose(fp);
    memcpy(cpu->bus.dram.mem, script, len*sizeof(uint8_t));
    free(script);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("%s", "risky:\e[1;31m error:\e[0m\e[1m no input files\e[1m\n");
        return 1;
    }
    if (strcmp(argv[1], "--help") == 0) {
        printf(
            "risky | the very small risc-v emulator\n"
            "\nrisky version 0.10 (tangerine)\n"
            "\nusage: risky [options] file\n"
            "\noptions:\n"
            "\t--help              | Displays this message\n"
            "\t--license           | Displays the license to risky\n"
            "\t--contributors      | Displays the contributors of risky\n"
            "\t--version           | Displays the version of risky\n"
            "\t=======================================================\n"
            "\t--file [file]       | Runs file\n"
            "\t--debug [file]      | Runs file in debug mode\n"
        );
        return 0;
    } else if (strcmp(argv[1], "--license") == 0) {
        // Print the license.
        return 1;
    } else if (strcmp(argv[1], "--version") == 0) {
        printf("%s", "risky version 0.10 (\e[33mtangerine\e[0m)\n");
        return 0;
    } else if (strcmp(argv[1], "--file") == 0) {
        if (argc <= 2) {
            printf("no file provided.\n");
            return 0;
        } 
        static CPU RISCV;
        cpu_init(&RISCV);
        read_file(&RISCV, argv[2]);
        while (1) {
            uint32_t inst = cpu_fetch(&RISCV);
            RISCV.pc += 4;
            if (!cpu_exec(&RISCV, inst)) break;
            if (RISCV.pc == 0) break;
        };
        toString(RISCV);
    } 
    return 0;
}