/*
 * Interrupt Service Routines
 */
#ifndef _ISR_H_
#define _ISR_H_

#include "../../../../library/include/types.h"

/*
 *
 */
typedef struct cpu_state_struct
{
  // Order DOES matter here

	uint32_t ds; // Data segment selector

	// Pushed by pusha/popped by popa in that order
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;

	uint32_t int_no, err_code; // Interrupt number and error code (if applicable)
	uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} cpu_state;


/*
 *
 */
cpu_state* Isr_Handler(cpu_state *status);

#endif // #ifndef _ISR_H_
