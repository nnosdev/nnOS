/*
 * Interrupt Service Routines
 */
#include "../../../../debug/include/debug.h"
#include "../include/InterruptServiceRoutines.h"
#include "../../../../common/kernel/include/Scheduler.h"
#include "../include/GlobalDescriptorTable.h"

extern Scheduler *scheduler;
extern tss_entry_t tss_entry;

cpu_state* Isr_Handler(cpu_state *state) {

	if (state->int_no <= 0x1F) {
		dprint("[ISR] Exception captured. Kernel stopped.");

		dprint("CPU State:");
		dprint("     INT: %d, RING: %d, ERRCODE: 0x%X\n"
				"\n"
				"     EAX: 0x%X EBP: 0x%X EBX: 0x%X ECX: 0x%X\n"
				"     EDI: 0x%X EDX: 0x%X EIP: 0x%X ESI: 0x%X\n"
				"     ESP: 0x%X EFLAGS: 0x%X\n"
				"     CS:  0x%X DS:  0x%X SS:  0x%X", state->int_no,
				state->useresp, state->err_code, state->eax, state->ebp, state->ebx,
				state->ecx, state->edi, state->edx, state->eip, state->esi,
				state->esp, state->eflags, state->cs, state->ds, state->ss);

		while (1) {
			// Stop CPU
			asm volatile ("cli; hlt");
		}
	}
	// Hardware-Interrupts
	if (state->int_no >= 0x20 && state->int_no <= 0x2f) {

		dprint("[ISR] Hardware interrupt 0x%X received.", state->int_no);
	  dprint("     INT: %d, RING: %d, ERRCODE: 0x%X\n"
	          "\n"
	          "     EAX: 0x%X EBP: 0x%X EBX: 0x%X ECX: 0x%X\n"
	          "     EDI: 0x%X EDX: 0x%X EIP: 0x%X ESI: 0x%X\n"
	          "     ESP: 0x%X EFLAGS: 0x%X\n"
	          "     CS:  0x%X DS:  0x%X SS:  0x%X\n",
	          state->int_no, state->useresp, state->err_code,
	          state->eax,    state->ebp,     state->ebx,      state->ecx,
	          state->edi,    state->edx,     state->eip,      state->esi,
	          state->esp,    state->eflags,
	          state->cs,     state->ds,      state->ss);

	  //uint32_t tss[32] = { 0x00, 0x00, 0x10 };

		// Call Scheduler
		if (state->int_no == 0x20) {
			state = Scheduler_Schedule(scheduler, state);
		}

		if (state->int_no >= 0x28) {
			// TODO Keyboard driver
			outb(0xA0, 0x20);
		}

		outb(0x20, 0x20); // End of interrupt (EOI)
		return state;
	}

	dprint("[ISR] Received (but unhandled) interrupt: 0x%X error code: 0x%X", state->int_no, state->err_code);

	asm volatile ("cli; hlt");
	return 0;
}
