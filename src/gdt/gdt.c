#include "gdt.h"
#include "../vga_utils/util.h"

// For extra information see wiki.osdev.org/Global_Descriptor_Table

extern void gdt_flush(uint32_t);
extern void tss_flush();

struct gdt_entry_struct gdt_entries[6]; // 6 entries: null, kernel code, kernel data, user code, user data, TSS
struct gdt_ptr_struct gdt_ptr;
struct tss_entry_struct tss_entry;
void initGdt() // initialize the GDT
{
	gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 6) - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

	setGdtGate(0, 0, 0, 0, 0);				  // Null segment
	setGdtGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code Segment
	setGdtGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data Segment
	setGdtGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code Segment
	setGdtGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Data Segment
	writeTSS(5, 0x10, 0x0);
	gdt_flush((uint32_t)&gdt_ptr);
	tss_flush();
}

void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0) // write the TSS entry to the GDT
{
	uint32_t base = (uint32_t)&tss_entry;
	uint32_t limit = base + sizeof(tss_entry);

	setGdtGate(num, base, limit, 0xE9, 0x00);
	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0 = ss0;
	tss_entry.esp0 = esp0;
	tss_entry.cs = 0x08 | 0x3;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;
}

void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) // set a GDT gate
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit = (limit & 0xFFFF);
	gdt_entries[num].flags = (limit >> 16) & 0x0F;
	gdt_entries[num].flags |= (gran & 0xF0);
	gdt_entries[num].access = access;
}
