#!/bin/sh

echo "Open a different terminal and enter this command: gdb <your_kernel_binary>, then inside of gdb, type: target remote :1234 and debug!"
qemu-system-i386 -s -S kernel.iso