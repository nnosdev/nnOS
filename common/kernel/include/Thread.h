/*
 * Thread
 */
#include "../../../library/include/types.h"
#include "../../../arch/x86/common/include/InterruptServiceRoutines.h"

#ifndef _THREAD_H_
#define _THREAD_H_


typedef struct
{
	// CPU state
	cpu_state cpu;
} Thread;



/*
 *
 */
void Thread_Init(Thread *self, uint32_t *entry, uint8_t *stack);


#endif // #ifndef _THREAD_H_
