/*
 *
 */

#include "../include/debug.h"
#include "../../arch/x86/ports/include/Ports.h"

#ifdef _DEBUG_H_

/*void dprintf(char* c)
 {
 int i;

 for (i = 0; c[i] != '\0'; i++)
 {
 outb(0x3F8, c[i]);
 }
 }*/

void dprintf(const char* c, ...)
{
	int i;

	for (i = 0; c[i] != '\0'; i++)
	{
		outb(0x3F8, c[i]);
	}
}

#endif // #ifdef _DEBUG_
