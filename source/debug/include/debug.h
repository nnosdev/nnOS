/*
 *
 */
#define DEBUG_MODE

#ifndef DEBUG_MODE

#define DEBUG(s)

#else

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "../../library/include/types.h"
#include "../../arch/x86/ports/include/Ports.h"


/*
 * TODO: Find a macro with variable arguments. And replace
 * 		all dprint() with that macro. DEBUG(s, ...)
 * 		Hint: __VA_ARGS__
 */
#define DEBUG(s) dprint(s)


static const byte_t DLARGECHARS = 0x01;


/**
 *
 */
void dprint(const char* chr, ...);

/*
 *
 */
void dprintchar(const char chr, byte_t color, byte_t x, byte_t y);

/*
 *
 */
void dprintnum(int num, uint16_t base, byte_t flag);

#endif // #ifndef _DEBUG_H_

#endif // #ifdef DEBUG_MODE
