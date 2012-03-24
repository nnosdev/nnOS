# Main Makefile

SRCS = $(shell find -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CC = gcc
AS = nasm
LD = ld

ASFLAGS = -f elf
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc #-Wformat=2 #-Werror (makes warnings to errors)
LDFLAGS = -melf_i386 -Tkernel.ld 

nnOS: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.S
	$(AS) $^ $(ASFLAGS) -o $@

clean:
	rm $(OBJS)

# Compiles and starts the kernel
qemu:
	clear
	make
	qemu -kernel nnOS -serial stdio -d int
	
# Generates a dump-file of the whole kernel
odump:
	objdump -S --disassemble-all nnOS -M intel > nnOSdump

.PHONY: clean
