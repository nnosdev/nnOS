/*
 *
 */

#include "../../console/include/Terminal.h"

#include "../../../arch/x86/common/include/GlobalDescriptorTable.h"
#include "../../../arch/x86/common/include/InterruptDescriptorTable.h"
#include "../../../arch/x86/ports/include/SerialPort.h"
#include "../../../debug/include/debug.h"
#include "../../../library/include/stdio.h"



/*
 * startup is called in boot.S and starts up nnOS
 */
// TODO After multithreading: Let run in 64-bit mode
void startup(void) {

	dprint("");
	dprint("[DEBUG] Debug-Mode");

	Terminal tm;
	Terminal_Initialize(&tm, LIGHTGREEN, BLACK);

	Gdt_Init();
	Idt_Init();

	//asm volatile ("int $0x3");
	//asm volatile ("int $0x4");
	//asm volatile ("int $0x1F");
	//asm volatile ("int $0x2F");

	while(1);

	dprint("end reached and still alive..");
	print("end reached and still alive..");

}

