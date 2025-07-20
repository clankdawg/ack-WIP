#include "../vga_utils/vga.h"
#include "../gdt/gdt.h"
#include "../timer/timer.h"
#include "../interrupts/idt.h"
#include "../keyboard/keyboard.h"

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
	initKeyboard();

	__asm__ volatile("sti");

	for (;;)
	{
		__asm__ volatile("hlt");
	}
}
