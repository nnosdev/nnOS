/*
 * Thread
 */
#include "../include/Thread.h"


/*
 *
 */
cpu_state* Thread_Init(Thread *self, uint32_t *entry, uint8_t *stack,
    uint8_t *user_stack)
{
	cpu_state new_state = {

			//.ds = 0,

			.eax = 0,
			.ebx = 0,
			.ecx = 0,
			.edx = 0,
			.esi = 0,
			.edi = 0,
			.ebp = 0,
			.esp = (uint32_t) user_stack + 0x1000,
			.eip = (uint32_t) entry,

			/* Ring-0-Segmentregister */
			.cs = 0x8,//0x18 | 0x03,
			//.ss = 0x20 | 0x03,

			/* Turn on IRQ (IF = 1) */
			.eflags = 0x202,

			//.useresp = 0,
	};

	/*
	 * Copying the new cpu-state on the thread stack let it looks like
	 * the thread has been interrupted by an interrupt. That way the
	 * scheduler will just start scheduling this new thread.
	 */
	cpu_state *state = (void*) (user_stack + STACK_SIZE - sizeof(new_state));

	*state = new_state;

	return state;
}
