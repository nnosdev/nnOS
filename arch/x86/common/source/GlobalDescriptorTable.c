/*
 *
 */
#include "../include/GlobalDescriptorTable.h"

static gdt_entry_container gdt;
static gdt_ptr_s gdt_ptr;

/*
 *
 */
static void Gdt_SetEntry(uint32_t index,
		uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

/*
 *
 */
static void Gdt_InstallEntries();




void Gdt_Init() {

	Gdt_InstallEntries();
}

/*
 *
 */
static void Gdt_SetEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access,
		uint8_t gran) {

	gdt.entry[index].limit_low = (limit & 0xFFFF);

	gdt.entry[index].base_low = (base & 0xFFFF);

	gdt.entry[index].base_middle = (base >> 16) & 0xFF;

	gdt.entry[index].access = access;

	gdt.entry[index].granularity = ((limit >> 16) & 0x0F) | ((gran << 4) & 0xF0);

	gdt.entry[index].base_high = (base >> 24) & 0xFF;
}

/*
 *
 */
static void Gdt_InstallEntries() {

	dprint("[GDT] Initializing GDT");

	gdt_ptr.limit = (GDT_ENTRIES * sizeof(gdt_entry)) - 1;
	gdt_ptr.base = (int) &gdt.entry[0];

	Gdt_SetEntry(0, 0, 0, 0, 0);
	Gdt_SetEntry(1, 0, 0xFFFFFFFF, GDT_ACC_R0_CODE, GDT_FLG);
	Gdt_SetEntry(2, 0, 0xFFFFFFFF, GDT_ACC_R0_DATA, GDT_FLG);
	Gdt_SetEntry(3, 0, 0xFFFFFFFF, GDT_ACC_R3_CODE, GDT_FLG);
	Gdt_SetEntry(4, 0, 0xFFFFFFFF, GDT_ACC_R3_DATA, GDT_FLG);

	dprint("[GDT] sizeof gdt_entry %d Bytes", sizeof(gdt_entry));
	dprint("[GDT] gdt_ptr.base 0x%X", gdt_ptr.base);
	dprint("[GDT] gdt_ptr.limit 0x%X (GDT size %d Bytes)", gdt_ptr.limit,
			gdt_ptr.limit + 1);
	dprint("[GDT] entry 1 0x%X", &gdt.entry[0]);
	dprint("[GDT] entry 2 0x%X", &gdt.entry[1]);
	dprint("[GDT] entry 3 0x%X", &gdt.entry[2]);
	dprint("[GDT] entry 4 0x%X", &gdt.entry[3]);
	dprint("[GDT] entry 5 0x%X", &gdt.entry[4]);

	Gdt_Flush((uint32_t) &gdt_ptr);

	dprint("[GDT] Returning from Gdt_Flush()");
}

