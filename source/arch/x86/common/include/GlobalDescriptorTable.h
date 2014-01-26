/*
 *
 */
#include "../../../../debug/include/debug.h"
#include "../../../../library/include/types.h"


#ifndef _GDT_H_
#define _GDT_H_

#define GDT_ENTRIES 6


#define ACC_PRES(x) (((x) << 0x07) & 0x80) // Present-Bit: 1 for active entry
#define ACC_RING(x) (((x) << 0x05) & 0x60) // Privilege: Ring 0 to 3
#define ACC_TYPE(x) (((x) << 0x4) & 0x10)  // Type: 1 for Code/Data segment 0 for system

#define ACC_DATA_RD        0x00 // Read-Only
#define ACC_DATA_RDA       0x01 // Read-Only, accessed
#define ACC_DATA_RDWR      0x02 // Read/Write
#define ACC_DATA_RDWRA     0x03 // Read/Write, accessed
#define ACC_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define ACC_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define ACC_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define ACC_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define ACC_CODE_EX        0x08 // Execute-Only
#define ACC_CODE_EXA       0x09 // Execute-Only, accessed
#define ACC_CODE_EXRD      0x0A // Execute/Read
#define ACC_CODE_EXRDA     0x0B // Execute/Read, accessed
#define ACC_CODE_EXC       0x0C // Execute-Only, conforming
#define ACC_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define ACC_CODE_EXRDC     0x0E // Execute/Read, conforming
#define ACC_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define FLG_GRAN(x) (((x) << 0x03) & 0x08) // Granularity: 0 limit 1B, 1 limit 4KiB
#define FLG_SIZE(x) (((x) << 0x02) & 0x04) // 0: 16 bit PM 1: 32 bit PM
#define FLG_LONG(x) (((x) << 0x01) & 0x02) // Long Mode: 0: ProtectedM 1: LongM
#define FLG_AVL(x) ((x) & 0x01) // Not used



/* The access-byte */
#define GDT_FLG_TSS 0x09

#define GDT_ACC_R0_CODE ACC_PRES(1) | ACC_RING(0) | ACC_TYPE(1) \
						| ACC_CODE_EXRD

#define GDT_ACC_R0_DATA ACC_PRES(1) | ACC_RING(0) | ACC_TYPE(1) \
						| ACC_DATA_RDWR

#define GDT_ACC_R3_CODE ACC_PRES(1) | ACC_RING(3) | ACC_TYPE(1) \
						| ACC_CODE_EXRD

#define GDT_ACC_R3_DATA ACC_PRES(1) | ACC_RING(3) | ACC_TYPE(1) \
						| ACC_DATA_RDWR

#define GDT_FLG FLG_GRAN(1) | FLG_SIZE(1) | FLG_LONG(0) | FLG_AVL(0)

#define GDT_TSS GDT_FLG_TSS | ACC_RING(3) | ACC_PRES(1)


/*
 *
 */
struct tss_entry_struct {
  uint16_t prev_tss;

  // loaded when program switches to kernel mode
  uint32_t esp0;  // kernel mode (ring0) stack pointer
  uint16_t ss0;   // kernel mode (ring0) segment

  uint32_t esp1;
  uint16_t ss1;

  uint32_t esp2;
  uint16_t ss2;

  uint32_t cr3;
  uint32_t eip;
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;

  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;

  uint16_t es;
  uint16_t cs;
  uint16_t ss;
  uint16_t ds;
  uint16_t fs;
  uint16_t gs;

  uint32_t ldt; // unused

  uint16_t trap;
  uint16_t iomap_base;
} __attribute__((packed));
typedef struct tss_entry_struct tss_entry_t;


/*
 *
 */
struct gdt_entry_struct {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
}__attribute__ ((packed));
typedef struct gdt_entry_struct gdt_entry;

/*
 *
 */
struct gdt_entry_container_struct {
	gdt_entry entry[GDT_ENTRIES];
}__attribute__ ((packed));
typedef struct gdt_entry_container_struct gdt_entry_container;

/*
 *
 */
struct gdt_ptr_struct {
	uint16_t limit;
	uint32_t base;
} __attribute__ ((packed));
typedef struct gdt_ptr_struct gdt_ptr_s;




// ASM function Gdt_Flush() can be found in gdt.S
extern void Gdt_Flush(uint32_t);

/*
 *
 */
void Gdt_Init();



#endif // #ifndef _GDT_H_
