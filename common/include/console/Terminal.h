/*
 * Terminal
 */
#include "../../../arch/x86/ports/include/Ports.h"
#include "../../../debug/include/debug.h"
#include "../../../library/include/types.h"


#ifndef _TERMINAL_H_
#define _TERMINAL_H_

/* Every row above the 200th line is going to be lost */
#define MAXCOLS 80
#define MAXROWS 200
#define MAXROWDISPLAY 25 // Only 25 rows can be displayed at once

/* The base address where we can access the terminal-content */
#define TERMINALBASE 0xB8000

/* Possible colors for text displayed */
typedef struct
{
	uint8 x;
	uint8 y;
} Position8;

// Allowed color-codes
typedef enum
{
	BLACK = 0x0,
	BLUE = 0x1,
	GREEN = 0x2,
	CYAN = 0x3,
	RED = 0x4,
	MAGENTA = 0x5,
	BROWN = 0x6,
	LIGHTGREY = 0x7,
	DARKGREY = 0x8,
	LIGHTBLUE = 0x9,
	LIGHTGREEN = 0xA,
	LIGHTCYAN = 0xB,
	LIGHTRED = 0xC,
	LIGHTMAGENTA = 0xD,
	YELLOW = 0xE,
	WHITE = 0xF
} COLOR;

typedef struct
{

	// Represents the position of the cursor
	Position8 m_position;

	// Contains 25 rows that will be displayed and
	// additional 75 rows as buffer for scrolling
	uint16 *m_content;

	// Displayed font-color
	uint8 m_fontcolor;

	// Displayed background color
	uint8 m_bgcolor;



} Terminal;

/*
 *
 */
void Terminal_Initialize(Terminal *self, COLOR fontcolor, COLOR bgcolor);

/*
 *
 */
void Terminal_ClearContent(Terminal *self);

/*
 *
 */
void Terminal_UpdateCursor(Terminal *self);

/*
 *
 */
void Terminal_Fontcolor(Terminal *self);

/*
 *
 */
void Terminal_WriteLine(Terminal *self);


#endif // #ifndef _TERMINAL_H_
