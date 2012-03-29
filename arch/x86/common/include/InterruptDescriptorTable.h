/*
 *
 */
#include "../../../../debug/include/debug.h"
#include "../../../../library/include/types.h"
#include "../../../../library/include/cstring.h"

extern Idt_Flush(uint32);

//#define IRQ_HANDLER(x) extern "C" void isr##x();


#ifndef _IDT_H_
#define _IDT_H_

#define IDT_ENTRIES 256

#define IDT_PRES(x) (((x) << 7) & 0x80) // 0: unused interrupts or paging
#define IDT_PRIV(x) (((x) << 5) & 0x60) // Defines Ring
#define IDT_STOR(x) (((x) << 4) & 0x10) // 0: for interrupt gate
#define IDT_TYPE(x) ((x) & 0x0F) // 0xE for 80386 32-bit interrupt gate

#define IDT_32BINT_PRESENT IDT_PRES(1) | IDT_PRIV(0) | IDT_STOR(0) | IDT_TYPE(14)

/*
 *
 */
struct idt_entry_struct
{
	uint16 base_lo; // Lower 16 bit of address to jump to when int fires
	uint16 sel;		// Kernel segment selector
	uint8 ist;		// Always zero
	uint8 flags;	// Flags (see documentation)
	uint16 base_hi; // Upper 16 bit of address to jump to when int fires
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
	uint16 limit;
	uint32 base;	// Address of the first element in idt
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_s;


static idt_entry_container idt;
static idt_ptr_s idt_ptr;


/*
 *
 */
void Idt_Init();

/*
 *
 */
static void Idt_SetEntry(uint8 index, uint32 base, uint16 sel, uint16 flags);

/*
 *
 */
static void Idt_InstallEntries();


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


#endif // #ifndef _IDT_H
