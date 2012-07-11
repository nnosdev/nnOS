/*
 * Thread
 */
#ifndef _THREAD_H_
#define _THREAD_H_


#include "../../../debug/include/debug.h"
#include "../../../library/include/types.h"
#include "../../../arch/x86/common/include/InterruptServiceRoutines.h"


#define STACK_SIZE 4096


typedef struct
{
	int bla;
} Thread;



/*
 *
 */
cpu_state* Thread_Init(Thread *self, uint32_t *entry, uint8_t *stack);


#endif // #ifndef _THREAD_H_
