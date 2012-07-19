#ifndef _PORTS_H_
#define _PORTS_H_

#include "../../../../library/include/types.h"


/*
 *
 */
static inline uint8_t inb(uint16_t port)
{
   uint8_t return_val;
   __asm__ __volatile__ (
   "inb %1,%0"
   : "=a"(return_val)
   : "d"(port));

   return return_val;
}


/*
 *
 */
static inline void outb(uint16_t port, uint8_t val)
{
   __asm__ __volatile__ (
   "outb %b0, %w1"
   :
   : "a"(val), "d"(port));
}

#endif
