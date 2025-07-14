gcc = /usr/opt/cross/bin/i686-elf-gcc
CFLAGS = -ffreestanding -Wall -Wextra -g -O2
SFLAGS = -f elf32

all: clean kernel boot image

clean:
	rm -rf /src/*/*.o && rm -rf kernel.iso && rm -rf src/boot/kernel && rm -rf src/*/*.o

kernel:
	$(gcc) $(CFLAGS) -c src/kernel/kernel.c -o src/kernel/kernel.o
	$(gcc) $(CFLAGS) -c src/vga_utils/vga.c -o src/vga_utils/vga.o
	$(gcc) $(CFLAGS) -c src/gdt/gdt.c -o src/gdt/gdt.o
	$(gcc) $(CFLAGS) -c src/vga_utils/util.c -o src/vga_utils/util.o
	$(gcc) $(CFLAGS) -c src/interrupts/idt.c -o src/interrupts/idt.o
boot:
	nasm $(SFLAGS) src/kernel/boot.s -o src/kernel/boot.o
	nasm $(SFLAGS) src/gdt/gdt.s -o src/gdt/gdts.o
	nasm $(SFLAGS) src/interrupts/idt.s -o src/interrupts/idts.o

image:
	ld -m elf_i386 -T linker.ld -o kernel src/kernel/boot.o src/kernel/kernel.o src/vga_utils/vga.o src/gdt/gdt.o src/gdt/gdts.o src/vga_utils/util.o src/interrupts/idt.o src/interrupts/idts.o
	mv kernel src/boot/kernel
	grub-mkrescue -o kernel.iso src/boot
	rm src/*/*.o
qemu:
	qemu-system-i386 kernel.iso