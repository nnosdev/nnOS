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
static uint8_t stack_a_user[STACK_SIZE];
static uint8_t stack_b[STACK_SIZE];
static uint8_t stack_b_user[STACK_SIZE];

void task_a(void)
{
    while (1) {
        print("O.");
    }
}

void task_b(void)
{
    while (1) {
        print(".O");
    }
}

Scheduler *scheduler;



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

	Thread init_threads[2];
	cpu_state *init_states[2];
	init_states[0] = Thread_Init(&init_threads[0], (uint32_t*)&task_a, stack_a, stack_a_user);
	init_states[1] = Thread_Init(&init_threads[1], (uint32_t*)&task_b, stack_b, stack_b_user);

	Scheduler_Init(scheduler, init_states, 2);

	// Enable hardware interrupts
	Idt_EnableHardwareInterrupts();

	dprint("lets go ..");

	while(1);

	dprint("end reached and still alive..");
	print("end reached and still alive..");
}

