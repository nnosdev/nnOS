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
void Idt_Init(void);

/*
 *
 */
void Idt_EnableHardwareInterrupts(void);


// TODO Clean this up by writing a macro
extern void  isr0 (void);
extern void  isr1 (void);
extern void  isr2 (void);
extern void  isr3 (void);
extern void  isr4 (void);
extern void  isr5 (void);
extern void  isr6 (void);
extern void  isr7 (void);
extern void  isr8 (void);
extern void  isr9 (void);
extern void isr10 (void);
extern void isr11 (void);
extern void isr12 (void);
extern void isr13 (void);
extern void isr14 (void);
extern void isr15 (void);
extern void isr16 (void);
extern void isr17 (void);
extern void isr18 (void);
extern void isr19 (void);
extern void isr20 (void);
extern void isr21 (void);
extern void isr22 (void);
extern void isr23 (void);
extern void isr24 (void);
extern void isr25 (void);
extern void isr26 (void);
extern void isr27 (void);
extern void isr28 (void);
extern void isr29 (void);
extern void isr30 (void);
extern void isr31 (void);

// IRQ 0-15
extern void isr32 (void);
extern void isr33 (void);
extern void isr34 (void);
extern void isr35 (void);
extern void isr36 (void);
extern void isr37 (void);
extern void isr38 (void);
extern void isr39 (void);
extern void isr40 (void);
extern void isr41 (void);
extern void isr42 (void);
extern void isr43 (void);
extern void isr44 (void);
extern void isr45 (void);
extern void isr46 (void);
extern void isr47 (void);

extern void isr48 (void); // Reserved for system calls

#endif // #ifndef _IDT_H
