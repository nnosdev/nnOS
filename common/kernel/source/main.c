/*
 *
 */

#include "../include/Scheduler.h"
#include "../include/Thread.h"

#include "../../console/include/Terminal.h"

#include "../../../arch/x86/common/include/GlobalDescriptorTable.h"
#include "../../../arch/x86/common/include/InterruptDescriptorTable.h"
#include "../../../arch/x86/ports/include/SerialPort.h"
#include "../../../debug/include/debug.h"
#include "../../../library/include/stdio.h"

static uint8_t stack_a[STACK_SIZE];
static uint8_t stack_b[STACK_SIZE];

void task_a(void)
{
    while (1) {
        print("A");
    }
}

void task_b(void)
{
    while (1) {
        print("B");
    }
}

Scheduler *scheduler;




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

	Thread init_threads[2];
	cpu_state *init_states[2];
	init_states[0] = Thread_Init(&init_threads[0], (uint32_t*)&task_a, stack_a);
	init_states[1] = Thread_Init(&init_threads[1], (uint32_t*)&task_b, stack_b);

	Scheduler_Init(scheduler, init_states, 2);

	dprint("lets go ..");
	//asm volatile ("int $0x3");
	while(1);


	dprint("end reached and still alive..");
	print("end reached and still alive..");
}

