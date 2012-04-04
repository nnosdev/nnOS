/*
 * Interrupt Service Routines
 */
#include "../include/InterruptServiceRoutines.h"
#include "../../../../debug/include/debug.h"

void Isr_Handler(cpu_state status)
{
	if(status.int_no <= 0x1F) {
		dprint("[ISR] Exception captured. Kernel stopped.");

		dprint( "CPU State:");
		dprint( "     INT: %d, RING: %d, ERRCODE: 0x%X\n"
				"\n"
				"     EAX: 0x%X EBP: 0x%X EBX: 0x%X ECX: 0x%X\n"
				"     EDI: 0x%X EDX: 0x%X EIP: 0x%X ESI: 0x%X\n"
				"     ESP: 0x%X EFLAGS: 0x%X\n"
				"     CD:  0x%X DS:  0x%X SS:  0x%X",
				status.int_no, 	status.usersp,	status.err_code,
				status.eax,	status.ebp, 	status.ebx, status.ecx,
				status.edi, status.edx,		status.eip, status.esi,
				status.esp,	status.eflags,
				status.cd,	status.ds, 		status.ss);
		while(1) {
			// Stop CPU
			asm volatile ("cli; hlt");
		}
	} else if (status.int_no >= 0x20 && status.int_no <= 0x2f) {

		dprint("[ISR] Hardware interrupt 0x%X received.", status.int_no);

		// TODO Keyboard driver

	    if (status.int_no >= 0x28) {
	        outb(0xA0, 0x20);
	    }

	    outb(0x20, 0x20); // EOI
	    return;
	}

	dprint("[ISR] Received (but unhandled) interrupt: 0x%X", status.int_no);
}
