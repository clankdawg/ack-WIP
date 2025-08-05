#include "../vga_utils/vga.h"
#include "../gdt/gdt.h"
#include "../timer/timer.h"
#include "../interrupts/idt.h"
#include "../keyboard/keyboard.h"
#include "../stdlib/stdio.h"
#include "../stdint/stdint.h"
#include "../memory/memory.h"
#include "../memory/multiboot.h"

void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info* bootInfo)
{
	Reset();
	initGdt();
	print("GDT initialized.\r\n");
	initIdt();
	print("IDT initialized.\r\n");
	initTimer();
	print("Kernel Loaded!\r\n");
	initKeyboard();		  // initialize everything

	uint32_t mod1 = *(uint32_t*)(bootInfo->mods_addr);
	uint32_t physicalAllocStart = (mod1 + 0xFFF) & ~0xFFF; // align to page size

	initMemory(bootInfo->mem_upper * 1024, physicalAllocStart); // initialize memory management
	print("\nMemory initialized.\r\n");

	__asm__ volatile("sti"); // then call assembly instruction to enable interrupts

	for (;;)
	{
		__asm__ volatile("hlt"); // halt the CPU until an interrupt occurs
	}
}
