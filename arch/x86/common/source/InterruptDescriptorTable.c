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
	dprint("[IDT] Initializing Entry %d on base %X", index, base);
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

	memset(&idt, 0, sizeof(idt_entry) * IDT_ENTRIES);

	//Idt_SetEntry(0, IRQ_HANDLER(x), 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(0, (uint32)isr0, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(1, (uint32)isr1, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(2, (uint32)isr2, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(3, (uint32)isr3, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(4, (uint32)isr4, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(5, (uint32)isr5, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(6, (uint32)isr6, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(7, (uint32)isr7, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(8, (uint32)isr8, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(9, (uint32)isr9, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(10, (uint32)isr10, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(11, (uint32)isr11, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(12, (uint32)isr12, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(13, (uint32)isr13, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(14, (uint32)isr14, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(15, (uint32)isr15, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(16, (uint32)isr16, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(17, (uint32)isr17, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(18, (uint32)isr18, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(19, (uint32)isr19, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(20, (uint32)isr20, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(21, (uint32)isr21, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(22, (uint32)isr22, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(23, (uint32)isr23, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(24, (uint32)isr24, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(25, (uint32)isr25, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(26, (uint32)isr26, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(27, (uint32)isr27, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(28, (uint32)isr28, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(29, (uint32)isr29, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(30, (uint32)isr30, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(31, (uint32)isr31, 0x08, IDT_32BINT_PRESENT);


	Idt_Flush((uint32) &idt_ptr);
}



