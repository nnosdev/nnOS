# Main Makefile 

SRCS = $(shell find -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))
OBJ = $(shell find -name '*.[o]')

CC = gcc
AS = nasm
LD = ld

ASFLAGS = -f elf
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -nostdlib -nodefaultlibs #-std=c99 -pedantic #-Wformat=2 #-Werror (makes warnings to errors)
LDFLAGS = -melf_i386 -Tkernel.ld 

nnOS: $(OBJS)
	$(LD) $(LDFLAGS) -o nnOS $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	mv $@ objects

%.o: %.S
	$(AS) $^ $(ASFLAGS) -o $@
	mv $@ objects

clean:
	rm $(OBJ)

# Compiles and starts the kernel
qemu:
	make
	clear
	qemu -kernel nnOS -serial stdio -d int
	make odump

# Compiles and starts the kernel. Delivers detailed assembler information
# in qemu.log
asm:
	make
	clear
	qemu -kernel nnOS -serial stdio -d in_asm
	make odump

# Compiles and starts the kernel and waits for gdb connection
gdb:
	make
	clear
	qemu -s -S -kernel nnOS -serial stdio -d int
	make odump
	
# Target needed for Eclipse
all:
	make

# Starts the kernel without compiling
fast:
	qemu -kernel nnOS -serial stdio -d int
	
# Generates a dump-file of the whole kernel
odump:
	objdump -S --disassemble-all nnOS -M intel > nnOSdump

.PHONY: clean
