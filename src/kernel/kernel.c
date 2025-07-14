#include "vga.h"
#include "gdt.h"

void kmain(void);

void kmain(void){
	initGdt();
	Reset(); // Clear screen
	print("GDT initialized.\r\n");
}
