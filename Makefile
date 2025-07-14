gcc = /usr/opt/cross/bin/i686-elf-gcc
CFLAGS = -ffreestanding -Wall -Wextra -g -O2
SFLAGS = -f elf32

all: clean kernel boot image

clean:
	rm -rf *.o && rm -rf kernel.iso && rm -rf src/boot/kernel && rm -rf src/interrupts/*.o

kernel:
	$(gcc) $(CFLAGS) -c src/kernel.c -o src/kernel.o
	$(gcc) $(CFLAGS) -c src/vga.c -o src/vga.o
	$(gcc) $(CFLAGS) -c src/gdt.c -o src/gdt.o
	$(gcc) $(CFLAGS) -c src/util.c -o src/util.o
	$(gcc) $(CFLAGS) -c src/interrupts/idt.c -o src/interrupts/idt.o
boot:
	nasm $(SFLAGS) src/boot.s -o src/boot.o
	nasm $(SFLAGS) src/gdt.s -o src/gdts.o
	nasm $(SFLAGS) src/interrupts/idt.s -o src/interrupts/idts.o

image:
	ld -m elf_i386 -T linker.ld -o kernel src/boot.o src/kernel.o src/vga.o src/gdt.o src/gdts.o src/util.o src/interrupts/idt.o src/interrupts/idts.o
	mv kernel src/boot/kernel
	grub-mkrescue -o kernel.iso src/boot
	rm src/*.o
qemu:
	qemu-system-i386 kernel.iso