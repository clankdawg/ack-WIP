#include "../vga_utils/vga.h"
#include "../gdt/gdt.h"
#include "../timer/timer.h"
#include "../interrupts/idt.h"
#include "../keyboard/keyboard.h"
#include "../stdlib/stdio.h"

void kmain(void);

void kmain(void)
{
	Reset();
	initGdt();
	print("GDT initialized.\r\n");
	initIdt();
	print("IDT initialized.\r\n");
	initTimer();
	print("Kernel Loaded!\r\n");
	initKeyboard(); // initialize everything

	__asm__ volatile("sti"); // then call assembly instruction to enable interrupts

	for (;;)
	{
		__asm__ volatile("hlt"); // halt the CPU until an interrupt occurs
	}
}
