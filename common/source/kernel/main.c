/*
 *
 */

#include "../../../debug/include/debug.h"
#include "../../../arch/x86/ports/include/SerialPort.h"
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

	//print("hi");

	for (a = 0; a < 3; a++) {
		address = *ptraddr;

		if (address != 0) {

			//DEBUG("COM found write a letter: ");
			SerialPort_Initialize(&port, address, 48, 0, 8);
			SerialPort_Write(&port, 65);
			DEBUG("\n");
		} else {
			//DEBUG("No COM found\n");
		}

		*ptraddr++;
	}

	print("yyyy%dyyA");



	DEBUG("still alive..\n");


}

