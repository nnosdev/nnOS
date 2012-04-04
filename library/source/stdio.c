/*
 *
 */
#include "../include/stdio.h"

/*
 *
 */
void print(const char *chr, ...) {
	int a = 0;
	int *args = (int *) (&chr + 1);

	while (*chr != 0) {

		if (*chr == '%') {

			chr++;

			switch (*chr) {
			case 'b':
				printnum(*args, 2, 0);
				args++;
				break;

			case 'd':
				printnum(*args, 10, 0);
				args++;
				break;

			case 'o':
				printnum(*args, 8, 0);
				args++;
				break;

			case 'x':
				printnum(*args, 16, 0);
				args++;
				break;

			case 'X':
				printnum(*args, 16, LARGECHARS);
				args++;
				break;
			}

		} else {
			printchar(*chr, 0xA, a, 0);
		}
		a++;
		chr++;
	}
}

/*
 *
 */
void printchar(const char chr, byte_t color, byte_t x, byte_t y) {
	uint16_t *off = (uint16_t*) 0xB8000;

	off += (uint16_t) y * 80 + x;

	*off = (((uint16_t) color) << 8) | chr;
}

/*
 *
 */
void printnum(int num, uint16_t base, byte_t flag) {

	const char *digits;
	static const char small_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	static const char large_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (flag & LARGECHARS)
		digits = large_digits;
	else
		digits = small_digits;

	if (base < 2 || base > 36)
		return;

	int i = 0;
	char out[100];

	if (num == 0) {
		out[i++] = '0';
	} else
		while (num != 0) {
			out[i++] = digits[num % base];
			num = num / base;
		}

	int a = 0;
	while (i != 0) {
		i--;
		printchar(out[i], 0xA, a++, 1);
	}

}

