#include "../stdint/stdint.h"
#include "../interrupts/idt.h"
#include "../vga_utils/vga.h"
#include "../vga_utils/util.h"
#include "keyboard.h"


void initKeyboard(){
    irq_install_handler(1,&keyboardHandler);
}



void keyboardHandler(struct InterruptRegisters *regs){
    
    char scanCode = inPortB(0x60) & 0x7F; 
    char press = inPortB(0x60) & 0x80; 
}