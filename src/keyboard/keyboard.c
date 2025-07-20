#include "../stdint/stdint.h"
#include "../interrupts/idt.h"
#include "../vga_utils/vga.h"
#include "../vga_utils/util.h"
#include "keyboard.h"

bool capsOn;
bool capslock;

void initKeyboard(){
    irq_install_handler(1,&keyboardHandler);
    capsOn = false;
    capslock = false;
    print("Keyboard Initialized!\r\n");
}



void keyboardHandler(struct InterruptRegisters *regs){
    
    char scanCode = inPortB(0x60) & 0x7F; // Which key pressed down
    char press = inPortB(0x60) & 0x80; // Key pressed down or released


    switch(scanCode){
        case 1:
        case 29:
        case 56:
        case 59:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 87:
        case 88:
            break;
        case 42:
            // shift
            if (press == 0){
                capsOn = true;
            }else{
                capsOn = false;
            }
        break;
        case 58:
            // caps
            if (!capslock && press == 0){
                capslock = true;
            }else if (capslock && press == 0){
                capslock = false;
            }
            break;
        default:
            if (press == 0){
                if (capsOn || capslock){
                    print("Capital key pressed.\r\n");
                }else{
                    print("Normal key pressed.\r\n");
                }
            }


    }

}