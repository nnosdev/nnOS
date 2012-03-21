#include "../../include/console/Terminal.h"


/*
 *
 */
void Terminal_Initialize(Terminal *self, COLOR fontcolor, COLOR bgcolor)
{
	self->m_position.x = 0;
	self->m_position.y = 24;
	self->m_fontcolor = fontcolor;
	self->m_bgcolor = bgcolor;

	Terminal_ClearContent(self);
	Terminal_UpdateCursor(self);
}

/*
 *
 */
void Terminal_ClearContent(Terminal *self)
{
	int x, y;

	// Clear screen
	for(x = 0; x < MAXCOLS; x++) {
		for(y = 0; y < MAXROWDISPLAY; y++) {
			self->m_content = ((uint16*) TERMINALBASE) + y * 80 + x;
			*self->m_content = (((uint16)self->m_fontcolor) << 8);
		}
	}
}

/*
 *
 */
void Terminal_UpdateCursor(Terminal *self)
{
	unsigned short pos =  self->m_position.y * 80 + self->m_position.x;

	// Cursor high-port to VGA index-register
	outb(0x3D4, 14);
	outb(0x3D5, (byte)(pos >> 8) & 0xFF);

	// Cursor low-port to VGA index-register
	outb(0x3D4, 15);
	outb(0x3D5, (byte)(pos & 0xFF));
}
