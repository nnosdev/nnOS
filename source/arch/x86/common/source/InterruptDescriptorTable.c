/*
 *
 */
#include "../include/InterruptDescriptorTable.h"

static idt_entry_container idt;
static idt_ptr_s idt_ptr;

/*
 *
 */
static void Idt_MapPicInterruptPorts();

/*
 *
 */
static void Idt_SetEntry(uint8_t index, uint32_t base, uint16_t sel, uint16_t flags);

/*
 *
 */
static void Idt_InstallEntries();




/*
 *
 */
void Idt_Init()
{
	dprint("[IDT] Initializing IDT");

	Idt_MapPicInterruptPorts();
	Idt_InstallEntries();
}

/*
 *
 */
void Idt_EnableHardwareInterrupts() {
	// Enable interrupts
	asm volatile("sti");
}

/*
 *
 */
static void Idt_MapPicInterruptPorts()
{
	dprint("[IDT] Initialize Programmable Interrupt Controller");

	// Master-PIC initialization
	outb(PIC_1_CTRL, PIC_ICW_1); 		// Initialization PIC (Master)
	outb(PIC_1_DATA, IRQ_0); 			// Interrupt number for IRQ 0 (PIT)
	outb(PIC_1_DATA, PIC_ICW_3_MASTER); // Slave connected to IRQ 2
	outb(PIC_1_DATA, PIC_ICW_2); 		// Enable 80x86 mode

	// Slave-PIC initialization
	outb(PIC_2_CTRL, PIC_ICW_1); 		// Initialization PIC (Master)
	outb(PIC_2_DATA, IRQ_8); 			// Interrupt number for IRQ 8
	outb(PIC_2_DATA, PIC_ICW_3_SLAVE); 	// Slave connected to IRQ 2
	outb(PIC_2_DATA, PIC_ICW_2); 		// Enable 80x86 mode

	// Null out data registers
	outb(PIC_1_DATA, PIC_ICW_4);
	outb(PIC_2_DATA, PIC_ICW_4);
}

/*
 *
 */
static void Idt_SetEntry(uint8_t index, uint32_t base, uint16_t sel, uint16_t flags)
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
	idt_ptr.limit = (IDT_ENTRIES * sizeof(idt_entry)) - 1;
	idt_ptr.base = (int) &idt.entry[0];

	memset(&idt, 0, sizeof(idt_entry) * IDT_ENTRIES);

	// Exceptions
	Idt_SetEntry(0, (uint32_t)isr0, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(1, (uint32_t)isr1, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(2, (uint32_t)isr2, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(3, (uint32_t)isr3, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(4, (uint32_t)isr4, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(5, (uint32_t)isr5, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(6, (uint32_t)isr6, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(7, (uint32_t)isr7, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(8, (uint32_t)isr8, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(9, (uint32_t)isr9, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(10, (uint32_t)isr10, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(11, (uint32_t)isr11, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(12, (uint32_t)isr12, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(13, (uint32_t)isr13, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(14, (uint32_t)isr14, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(15, (uint32_t)isr15, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(16, (uint32_t)isr16, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(17, (uint32_t)isr17, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(18, (uint32_t)isr18, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(19, (uint32_t)isr19, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(20, (uint32_t)isr20, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(21, (uint32_t)isr21, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(22, (uint32_t)isr22, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(23, (uint32_t)isr23, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(24, (uint32_t)isr24, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(25, (uint32_t)isr25, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(26, (uint32_t)isr26, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(27, (uint32_t)isr27, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(28, (uint32_t)isr28, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(29, (uint32_t)isr29, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(30, (uint32_t)isr30, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(31, (uint32_t)isr31, 0x08, IDT_32BINT_PRESENT);
	// IRQ 0-15
	Idt_SetEntry(32, (uint32_t)isr32, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(33, (uint32_t)isr33, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(34, (uint32_t)isr34, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(35, (uint32_t)isr35, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(36, (uint32_t)isr36, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(37, (uint32_t)isr37, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(38, (uint32_t)isr38, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(39, (uint32_t)isr39, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(40, (uint32_t)isr40, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(41, (uint32_t)isr41, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(42, (uint32_t)isr42, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(43, (uint32_t)isr43, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(44, (uint32_t)isr44, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(45, (uint32_t)isr45, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(46, (uint32_t)isr46, 0x08, IDT_32BINT_PRESENT);
	Idt_SetEntry(47, (uint32_t)isr47, 0x08, IDT_32BINT_PRESENT);
	// System calls
	Idt_SetEntry(48, (uint32_t)isr48, 0x08, IDT_32BINT_PRESENT);

	Idt_Flush((uint32_t) &idt_ptr);
}



