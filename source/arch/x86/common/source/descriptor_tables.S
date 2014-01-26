
; Method for flushing the Global Descriptor Table
global Gdt_Flush
Gdt_Flush:
	mov eax, [esp+4] 	; Get the pointer to the GDT, passed as parameter
	lgdt [eax]			; Load new GDT Pointer

	mov ax, 0x10		; 0x10 is the offset in the GDT to our data segment
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


extern Isr_Handler


%macro isr_stub 1
global isr%1
isr%1:
	cli
	push byte 0
	push byte %1
	jmp isr_common_stub
%endmacro

%macro isr_stub_error 1
global isr%1
isr%1:
	cli
	push byte %1
	jmp isr_common_stub
%endmacro


isr_common_stub:

	; save cpu state by pushing
	; main purpose registers onto the stack
	pusha  ; push eax
		   ; push ecx
		   ; push edx
		   ; push ebx
		   ; push esp
		   ; push ebp
		   ; push esi
		   ; push edi

	mov eax, ds
	push eax

	mov eax, 0x10
	mov ds, eax
    mov es, eax
    mov fs, eax
	mov gs, eax

	push esp ; parameter cpu_state*
	call Isr_Handler ; call interrupt handler
	mov esp, eax

	pop eax
	mov ds, eax
    ;mov es, eax
    ;mov fs, eax
	;mov gs, eax

	popa ; pop edi
		 ; pop esi
		 ; pop ebp
		 ; pop esp
		 ; pop ebx
		 ; pop edx
		 ; pop ecx
		 ; pop eax

	add esp, 8	; pop error code, interrupt number
	sti 				; enable interrupts

	iret				; interrupt return

isr_stub 0
isr_stub 1
isr_stub 2
isr_stub 3
isr_stub 4
isr_stub 5
isr_stub 6
isr_stub 7
isr_stub_error 8
isr_stub 9
isr_stub_error 10
isr_stub_error 11
isr_stub_error 12
isr_stub_error 13
isr_stub_error 14
isr_stub 15
isr_stub 16
isr_stub_error 17
isr_stub 18
isr_stub 19
isr_stub 20
isr_stub 21
isr_stub 22
isr_stub 23
isr_stub 24
isr_stub 25
isr_stub 26
isr_stub 27
isr_stub 28
isr_stub 29
isr_stub 30
isr_stub 31

; IRQs
isr_stub 32 ; IRQ 0
isr_stub 33 ; IRQ 1
isr_stub 34 ; IRQ 2
isr_stub 35 ; IRQ 3
isr_stub 36 ; IRQ 4
isr_stub 37 ; IRQ 5
isr_stub 38 ; IRQ 6
isr_stub 39 ; IRQ 7
isr_stub 40 ; IRQ 8
isr_stub 41 ; IRQ 9
isr_stub 42 ; IRQ 10
isr_stub 43 ; IRQ 11
isr_stub 44 ; IRQ 12
isr_stub 45 ; IRQ 13
isr_stub 46 ; IRQ 14
isr_stub 47 ; IRQ 15

isr_stub 48 ; System calls


