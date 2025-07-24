#include "../stdint/stdint.h"
#include "../vga_utils/util.h"
#include "../interrupts/idt.h"
#include "timer.h"
#include "../vga_utils/vga.h"

// PIT (Programmable Interval Timer) is used for timing events, so that tasks can be scheduled, and clocks can be updated.

uint64_t ticks;
const uint32_t freq = 100;
uint8_t timerticked = 0;

void onIrq0(struct InterruptRegisters *regs) // send signal to the CPU that the timer has ticked
{
    ticks += 1;

    if (!timerticked)
    {
        print("Timer loaded.\r\n");
        timerticked = 1;
    }
}

void initTimer()
{
    ticks = 0;
    irq_install_handler(0, &onIrq0);

    // Oscillator runs at 119318.16666 Hz
    uint32_t divisor = 1193180 / freq;

    // 0011 0110 - See wiki.osdev.org/Programmable_Interval_Timer
    outPortB(0x43, 0x36);                             // set the PIT to mode 3 (square wave generator)
    outPortB(0x40, (uint8_t)(divisor & 0xFF));        // write low byte of divisor
    outPortB(0x40, (uint8_t)((divisor >> 8)) & 0xFF); // write high byte of divisor

    __asm__ volatile("" ::: "memory"); // prevent compiler from optimizing out the above code
};