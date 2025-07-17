#include "../vga_utils/vga.h"
#include "../gdt/gdt.h"
#include "../timer/timer.h"
#include "../interrupts/idt.h"
#include "../stdlib/stdio.h"

void kmain(void);

void kmain(void)
{
	Reset();
	initGdt();
	printf("GDT initialized.\r\n");
	initIdt();
	printf("IDT initialized.\r\n");
	initTimer();
	printf("Kernel Loaded!\r\n");

	__asm__ volatile("sti");

	for (;;)
	{
		__asm__ volatile("hlt");
	}
}
