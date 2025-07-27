#include "../vga_utils/vga.h"
#include "../gdt/gdt.h"
#include "../timer/timer.h"
#include "../interrupts/idt.h"
#include "../keyboard/keyboard.h"
#include "../stdlib/stdio.h"
#include "../stdint/stdint.h"
#include "../bootconfig/memory.h"
#include "../bootconfig/multiboot.h"

char test[] = "Hello, World!\r\n";

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
	initMemory(bootInfo); // initialize memory management
	print("\nMemory initialized.\r\n");

	__asm__ volatile("sti"); // then call assembly instruction to enable interrupts

	for (;;)
	{
		__asm__ volatile("hlt"); // halt the CPU until an interrupt occurs
	}
}
