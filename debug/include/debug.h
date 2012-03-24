/*
 *
 */
#include "../../library/include/types.h"
#include "../../arch/x86/ports/include/Ports.h"



#define DEBUG_MODE

#ifndef DEBUG_MODE

#define DEBUG(s)

#else

#ifndef _DEBUG_H_
#define _DEBUG_H_


/*
 * TODO: Find a macro with variable arguments. And replace
 * 		all dprint() with that macro. DEBUG(s, ...)
 * 		Hint: __VA_ARGS__
 */
#define DEBUG(s) dprint(s)


static const byte DLARGECHARS = 0x01;


/**
 *
 */
void dprint(const char* chr, ...);

/*
 *
 */
void dprintchar(const char chr, byte color, byte x, byte y);

/*
 *
 */
void dprintnum(int num, uint16 base, byte flag);

#endif // #ifndef _DEBUG_H_

#endif // #ifdef DEBUG_MODE
