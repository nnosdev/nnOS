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
	qemu-system-i386 -kernel nnOS -serial stdio -d int

# Compiles and starts the kernel. Delivers detailed assembler information
# in qemu.log
asm:
	make
	clear
	qemu-system-i386 -kernel nnOS -serial stdio -d in_asm

# Compiles and starts the kernel and waits for gdb connection
gdb:
	make
	clear
	qemu-system-i386 -s -S -kernel nnOS -serial stdio -d int

# Updates the documentation of nnOS. 
doxy:
	doxygen docs/doxycfg
	
# Target needed for Eclipse
all:
	make
	qemu-system-i386 -kernel nnOS -serial stdio -d int

# Starts the kernel without compiling
fast:
	qemu-system-i386 -kernel nnOS -serial stdio -d int
	
# Generates a dump-file of the whole kernel
odump:
	objdump -S --disassemble-all nnOS -M intel > nnOSdump
 
.PHONY: clean
