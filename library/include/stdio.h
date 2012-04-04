/*
 *
 */
#include "types.h"

#ifndef _STDIO_H_
#define _STDIO_H_


static const byte_t LARGECHARS = 0x01;

/*
 *
 */
void print(const char *format, ...);

/*
 *
 */
void printchar(const char chr, byte_t color, byte_t x, byte_t y);

/*
 *
 */
void printnum(int num, uint16_t base, byte_t flag);


#endif // #ifndef _STDIO_H_
