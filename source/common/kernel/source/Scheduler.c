/*
 * Scheduler
 */
#include "../include/Scheduler.h"


static int current_task = -1;
static int num_tasks = 2;


/*
 *
 */
void Scheduler_Init(Scheduler *self, cpu_state *states[], uint16_t thread_count)
{
	dprint("[Scheduler] Initialization");

	if( thread_count >= MAX_THREADS ) {
		dprint("[Scheduler] MAX_THREADS %d exceeded", MAX_THREADS);
		return;
	}

	// Store thread_count
	self->thread_count = thread_count;

	// Initialize thread_states
	int x = 0;
	for(x = 0; x < thread_count; x++) {
		self->thread_states[x] = states[x];
	}
}

/*
 *
 */
cpu_state* Scheduler_Schedule(Scheduler *self, cpu_state *state)
{
	if(current_task >= 0) {
		self->thread_states[current_task] = state;
	}

	current_task++;
	current_task %= num_tasks;

	dprint("[Scheduler] Schedule to task %d next instruction 0x%X",
	    current_task, state->eip);

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

	state = self->thread_states[current_task];

	return state;
}
