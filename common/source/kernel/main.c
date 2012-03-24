/*
 *
 */

#include "../../include/console/Terminal.h"
#include "../../../arch/x86/ports/include/SerialPort.h"
#include "../../../debug/include/debug.h"
#include "../../../library/include/stdio.h"

#include "../../../arch/x86/common/include/GlobalDescriptorTable.h"
#include "../../../arch/x86/common/include/InterruptDescriptorTable.h"

/*
 * startup is called in boot.S and starts up nnOS
 */
void startup(void) {

	dprint("");
	dprint("[DEBUG] Debug-Mode");

	Terminal tm;
	Terminal_Initialize(&tm, LIGHTGREEN, BLACK);

	Gdt_Init();
	Idt_Init();

	dprint("end reached and still alive..");
	print("end reached and still alive..");

}

