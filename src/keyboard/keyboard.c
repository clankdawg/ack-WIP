#include "../stdint/stdint.h"
#include "../interrupts/idt.h"
#include "../vga_utils/vga.h"
#include "keyboard.h"


void initKeyboard(){
    irq_install_handler(1,&keyboardHandler);
}



void keyboardHandler(struct InterruptRegisters *regs){
    
    char scanCode = inPortB(0x60) & 0x7F; // What key has been pressed
    char press = inPortB(0x60) & 0x80; // Press down or release

    print("Scan Code: %d, Press: &d\n", scanCode, press);

}