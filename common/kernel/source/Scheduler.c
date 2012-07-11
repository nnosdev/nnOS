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

	dprint("[Scheduler] Schedule to task %d instruction 0x%X", current_task, state->eip);

	state = self->thread_states[current_task];

	return state;
}
