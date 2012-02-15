


section multiboot
MB_MODULEALIGN 	equ 0x0	;not used
MB_MEMINFO 		equ 0x0 ;not used
MB_FLAGS 		equ MB_MODULEALIGN | MB_MEMINFO
MB_MAGIC 		equ 0x1BADB002
MB_CHECKSUM 	equ -(MB_MAGIC + MB_FLAGS)

align 4
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHECKSUM

section .text

extern init

global _start
_start:
	mov esp, kernel_stack
	call init

_stop:
    cli
    hlt

    jmp _stop

section .bss
resb 8192	; 8kB stack
kernel_stack:
