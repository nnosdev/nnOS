/*
 * Interrupt Service Routines
 */
#include "../include/isr.h"
#include "../../../../debug/include/debug.h"

void isr_handler(registers_t regs)
{
   dprint("[ISR] Received (but unhandled) interrupt: 0x%X", regs.int_no);
}
