/*
 *
 */
#include "types.h"

#ifndef _STDIO_H_
#define _STDIO_H_


static const byte LARGECHARS = 0x01;

/*
 *
 */
void print(const char *format, ...);

/*
 *
 */
void printchar(const char chr, byte color, byte x, byte y);

/*
 *
 */
void printnum(int num, uint16 base, byte flag);


#endif // #ifndef _STDIO_H_
