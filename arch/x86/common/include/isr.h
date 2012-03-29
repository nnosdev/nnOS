/*
 *
 */
#include "../../../../library/include/types.h"


#ifndef _ISR_H_
#define _ISR_H_


typedef struct registers
{
   uint32 ds;                  // Data segment selector
   uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32 int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32 eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;


#endif // #ifndef _ISR_H_
