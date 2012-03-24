/*
 *
 */
#include "../include/InterruptDescriptorTable.h"

/*
 *
 */
void Idt_Init()
{
	Idt_InstallEntries();
}

/*
 *
 */
static void Idt_SetEntry(uint8 index, uint32 base, uint16 sel, uint16 flags)
{
	idt.entry[index].base_lo = base & 0xFFFF;

	idt.entry[index].sel = sel;

	idt.entry[index].ist = 0;

	idt.entry[index].flags = flags;

	idt.entry[index].base_hi = (base >> 16) & 0xFFFF;
}

/*
 *
 */
static void Idt_InstallEntries()
{
	dprint("[IDT] Initializing IDT");

	idt_ptr.limit = (IDT_ENTRIES * sizeof(idt_entry)) - 1;
	idt_ptr.base = (int) &idt.entry[0];

	// memset(&idt, 0, sizeof(idt_entry) * IDT_ENTRIES);

	// Idt_SetEntry(0, (uint32)isr0, 0x08, 0x8E);

	Idt_Flush((uint32) &idt_ptr);
}
