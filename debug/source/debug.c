/*
 *
 */
#include "../include/debug.h"


#ifdef _DEBUG_H_


/*
 *
 */
void dprint(const char *chr, ...) {

	int *args = (int *) (&chr + 1);

	while (*chr != 0) {

		if (*chr == '%') {

			chr++;

			switch (*chr) {
			case 'b':
				dprintnum(*args, 2, 0);
				args++;
				break;

			case 'd':
				dprintnum(*args, 10, 0);
				args++;
				break;

			case 'o':
				dprintnum(*args, 8, 0);
				args++;
				break;

			case 'x':
				dprintnum(*args, 16, 0);
				args++;
				break;

			case 'X':
				dprintnum(*args, 16, DLARGECHARS);
				args++;
				break;
			}

		} else {
			dprintchar(*chr, 0, 0, 0);
		}

		chr++;
	}

	dprintchar('\n', 0, 0, 0);
}

/*
 *
 */
void dprintchar(const char chr, byte_t color, byte_t x, byte_t y) {

	outb(0x3F8, chr);
}

/*
 *
 */
void dprintnum(int num, uint16_t base, byte_t flag) {

	const char *digits;
	static const char small_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	static const char large_digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (flag & DLARGECHARS)
		digits = large_digits;
	else
		digits = small_digits;

	if (base < 2 || base > 36)
		return;

	int i = 0;
	char out[100];

	if (num == 0) {
		out[i] = '0';
		i++;
	} else
		while (num != 0) {
			out[i] = digits[num % base];
			i++;
			num = num / base;
		}

	while (i != 0) {
		i--;
		dprintchar(out[i], 0, 0, 0);
	}
}

#endif // #ifdef _DEBUG_
