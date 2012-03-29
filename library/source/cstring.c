/*
 *
 */
#include "../include/cstring.h"
#include "../../debug/include/debug.h"

/*
 *
 */
void* memset(void *ptr, uint32 value, size_t bytes)
{
	if(bytes < 1)
		return 0;

	uint8 *pt = (uint8) ptr;

	while(bytes) {
		*pt = value;
		pt++;
		bytes--;
	}

	return ptr;
}
