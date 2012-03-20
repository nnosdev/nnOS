/*
 *
 */

#define _DEBUG_H_

#ifndef _DEBUG_H_

#define DEBUG(s)

#else

#define DEBUG(s) dprint(s"\0")
#define DEBUGX(s) dprint(s)

/**
 *
 */
void dprint(const char* c, ...);

#endif // #ifdef _DEBUG_H_
