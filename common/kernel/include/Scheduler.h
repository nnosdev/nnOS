/*
 * Scheduler
 */
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "../include/Thread.h"
#include "../../../library/include/types.h"
#include "../../../arch/x86/common/include/InterruptServiceRoutines.h"


#define MAX_THREADS 1024

/*
 *
 */
typedef struct
{
	uint16_t thread_count;
	cpu_state *thread_states[MAX_THREADS];
} Scheduler;


/*
 *
 */
void Scheduler_Init(Scheduler *self, cpu_state *states[], uint16_t thread_count);


/*
 *
 */
cpu_state* Scheduler_Schedule(Scheduler *self, cpu_state *state);

#endif // #ifndef _SCHEDULER_H_
