/*
 * Interrupt Service Routines
 */
#include "../../../../library/include/types.h"


#ifndef _ISR_H_
#define _ISR_H_


typedef struct cpu_state_struct
{
   uint32_t ds; 		// Data segment selector

   uint32_t edi;		// TODO Find description
   uint32_t esi;
   uint32_t ebp;
   uint32_t esp;
   uint32_t ebx;
   uint32_t edx;
   uint32_t ecx;
   uint32_t eax;

   uint32_t int_no; 	// Interrupt number
   uint32_t err_code; // Interrupt error code

   uint32_t eip; 		// TODO Find description
   uint32_t cd;
   uint32_t eflags;
   uint32_t usersp;
   uint32_t ss;
} cpu_state;

/*
 *
 */
void Isr_Handler(cpu_state status);


#endif // #ifndef _ISR_H_
