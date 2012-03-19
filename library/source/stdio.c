#include "../include/stdio.h"

#include "../../debug/include/debug.h"

/*
 *
 */
void print(const char *chr, ...) {

	int a = 0;

	while (*chr != 0) {

		if (*chr == '%') {

			chr++;

			switch (*chr) {
			case 'd':
				DEBUG("print a decimal figure here\n");
				break;
			}

		} else {
			printchar(chr, 0xA, a, 0);
		}

		a++;
		chr++;
	}
}

/*
 *
 */
void printchar(const char *chr, byte color, byte x, byte y) {
	uint16 *off = (uint16*) 0xB8000;

	off += (uint16) y * 80 + x;

	*off = (((uint16) color) << 8) | *chr;
}
