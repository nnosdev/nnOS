/*
 *
 */
#include "../../../../debug/include/debug.h"
#include "../../../../library/include/types.h"
#include "../../../../library/include/cstring.h"



#ifndef _IDT_H_
#define _IDT_H_


/*
 * IDT
 */
#define IDT_ENTRIES 256

#define IDT_PRES(x) (((x) << 7) & 0x80) // 0: unused interrupts or paging
#define IDT_PRIV(x) (((x) << 5) & 0x60) // Defines Ring
#define IDT_STOR(x) (((x) << 4) & 0x10) // 0: for interrupt gate
#define IDT_TYPE(x) ((x) & 0x0F) // 0xE for 80386 32-bit interrupt gate

#define IDT_32BINT_PRESENT IDT_PRES(1) | IDT_PRIV(0) | IDT_STOR(0) | IDT_TYPE(14)

/*
 * PIC
 */
#define PIC_ICW_1 0x11 // PIC Initialization Control Word
#define PIC_ICW_2 0x01 // Enable 80x86 mode
#define PIC_ICW_3_MASTER 0x04
#define PIC_ICW_3_SLAVE 0x02
#define PIC_ICW_4 0x00 // Null out data register

#define IRQ_0 0x20
#define IRQ_8 0x28

#define PIC_1_CTRL 0x20 // Primary (Master) PIC Command/Status register
#define PIC_2_CTRL 0xA0 // Secondary (Slave) PIC Command/Status register

#define PIC_1_DATA 0x21 // Primary (Master) PIC Interrupt Mask and Data register
#define PIC_2_DATA 0xA1 // Secondary (Slave) PIC Interrupt Mask and Data register



/*
 *
 */
struct idt_entry_struct
{
	uint16_t base_lo; 	// Lower 16 bit of address to jump to when int fires
	uint16_t sel;		// Kernel segment selector
	uint8_t ist;		// Always zero
	uint8_t flags;		// Flags (see documentation)
	uint16_t base_hi; 	// Upper 16 bit of address to jump to when int fires
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry;

/*
 *
 */
struct idt_entry_container_struct
{
	idt_entry entry[IDT_ENTRIES];
} __attribute__((packed));
typedef struct idt_entry_container_struct idt_entry_container;

/*
 *
 */
struct idt_ptr_struct
{
	uint16_t limit;
	uint32_t base;	// Address of the first element in IDT
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_s;


/*
 *
 */
extern Idt_Flush(uint32_t ptr);

/*
 *
 */
void Idt_Init();


// TODO Clean this up by writing a macro
extern void  isr0 ();
extern void  isr1 ();
extern void  isr2 ();
extern void  isr3 ();
extern void  isr4 ();
extern void  isr5 ();
extern void  isr6 ();
extern void  isr7 ();
extern void  isr8 ();
extern void  isr9 ();
extern void isr10 ();
extern void isr11 ();
extern void isr12 ();
extern void isr13 ();
extern void isr14 ();
extern void isr15 ();
extern void isr16 ();
extern void isr17 ();
extern void isr18 ();
extern void isr19 ();
extern void isr20 ();
extern void isr21 ();
extern void isr22 ();
extern void isr23 ();
extern void isr24 ();
extern void isr25 ();
extern void isr26 ();
extern void isr27 ();
extern void isr28 ();
extern void isr29 ();
extern void isr30 ();
extern void isr31 ();

// IRQ 0-15
extern void isr32 ();
extern void isr33 ();
extern void isr34 ();
extern void isr35 ();
extern void isr36 ();
extern void isr37 ();
extern void isr38 ();
extern void isr39 ();
extern void isr40 ();
extern void isr41 ();
extern void isr42 ();
extern void isr43 ();
extern void isr44 ();
extern void isr45 ();
extern void isr46 ();
extern void isr47 ();

extern void isr48 (); // System calls

#endif // #ifndef _IDT_H
