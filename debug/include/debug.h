/*
 *
 */

#define _DEBUG_H_

#ifndef _DEBUG_H_

#define DEBUG(s)

#else

#define DEBUG(s) dprintf(s"\0")
#define DEBUGX(s) dprintf(s)

/**
 *
 */
//void dprintf(char* c);
void dprintf(const char* c, ...);

#endif // #ifdef _DEBUG_H_
