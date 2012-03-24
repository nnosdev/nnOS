/*
 *
 */
#include "../../../../debug/include/debug.h"
#include "../../../../library/include/types.h"


#ifndef _IDT_H_
#define _IDT_H_

#define IDT_ENTRIES 256



/*
 *
 */
struct idt_entry_struct
{
	uint16 base_lo; // Lower 16 bit of address to jump to when int fires
	uint16 sel;		// Kernel segment selector
	uint8 ist;
	uint8 flags;
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


extern Idt_Flush(uint32);
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


#endif // #ifndef _IDT_H
