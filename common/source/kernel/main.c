/*
 *
 */

#include "../../include/console/Terminal.h"
#include "../../../arch/x86/ports/include/SerialPort.h"
#include "../../../debug/include/debug.h"
#include "../../../library/include/stdio.h"


/*
 * startup is called in boot.S and starts up nnOS
 */
void startup(void) {

	SerialPort port;

	unsigned long int *ptraddr;
	unsigned int address;

	ptraddr = (unsigned long int *) 0x00000400;

	address = *ptraddr;

	int a;
	for (a = 0; a < 3; a++) {
		address = *ptraddr;

		if (address != 0) {

			SerialPort_Initialize(&port, address, 48, 0, 8);
			SerialPort_Write(&port, 65);
			DEBUG("\n");
		}

		*ptraddr++;
	}

	Terminal tm;



	print("yyy%dy%byyA", 9, 2645);

	Terminal_Initialize(&tm, LIGHTGREEN, BLACK);

	print("relate this text to cursor position");


	DEBUG("\nend reached and still alive..\n");


}

