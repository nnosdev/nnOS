/*
 *
 */
#include "../include/cstring.h"
#include "../../debug/include/debug.h"

/*
 *
 */
void* memset(void *ptr, uint32_t value, size_t bytes)
{
	if(bytes < 1)
		return 0;

	uint8_t *pt = (uint8_t) ptr;

	while(bytes) {
		*pt = value;
		pt++;
		bytes--;
	}

	return ptr;
}
