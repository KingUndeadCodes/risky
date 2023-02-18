CFLAGS := \
	-ffreestanding \
	-Wl,-Ttext=0x0 \
	-nostdlib \
	-march=rv64im \
	-mabi=lp64 \

all: build clean

build: make-c-tests make-asm-tests

make-obj-dir:
	mkdir objs

make-c-tests: make-obj-dir
	riscv64-unknown-elf-gcc -S src/main.c
	riscv64-unknown-elf-gcc $(CFLAGS) -o objs/test.o main.s
	riscv64-unknown-elf-objcopy -O binary objs/test.o bin/ctest.bin

make-asm-tests: make-obj-dir
	riscv64-unknown-elf-gcc $(CFLAGS) -o objs/math.o src/math.s
	riscv64-unknown-elf-gcc $(CFLAGS) -o objs/fibb.o src/fibb.s
	riscv64-unknown-elf-objcopy -O binary objs/math.o bin/mathtest.bin
	riscv64-unknown-elf-objcopy -O binary objs/fibb.o bin/fibbtest.bin

# Usefull links:
# 	-> ARCH: https://archriscv.felixc.at
# 	-> OSDEV: https://wiki.osdev.org/RISC-V_Bare_Bones
# 	-> BUILDROOT: https://github.com/cnlohr/buildroot 

clean:
	rm -f main.s
	rm -f objs/*.o
	rmdir objs