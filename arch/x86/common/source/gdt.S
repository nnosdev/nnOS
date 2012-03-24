
; Method for flushing the Global Descriptor Table
global Gdt_Flush
Gdt_Flush:
	mov eax, [esp+4] 	; Get the pointer to the GDT, passed as parameter
	lgdt [eax]			; Load new GDT Pointer

	mov ax, 0x10		; 0x10 is the offset in the GDT to out data segment
	mov ds, ax			; Load all data segment selectors
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush		; 0x08 is the offset to our code segment: Far jump
.flush:
	ret

; Method for flushing the Interrupt Descriptor Table
global Idt_Flush    	; Allows the C code to call idt_flush().
Idt_Flush:
	mov eax, [esp+4]  	; Get the pointer to the IDT, passed as a parameter.
   	lidt [eax]        	; Load the IDT pointer.
   	ret
