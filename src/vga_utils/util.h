#include "../stdint/stdint.h"

void *memset(void *dest, char val, uint32_t count);
void outPortB(uint16_t port, uint8_t value); // write byte to CPU port
char inPortB(uint16_t port);                 // read byte from CPU port

struct InterruptRegisters // structure for hardware interrupts
{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};
