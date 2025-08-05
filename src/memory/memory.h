#include "multiboot.h"

#define KERNEL_START 0xC0000000 // define the kernel start address
#define KERNEL_MALLOC 0xD0000000 // define the kernel malloc start address
#define PAGE_FLAG_PRESENT (1 << 0) // page present flag
#define PAGE_FLAG_WRITE (1 << 1)   // page writable flag

extern uint32_t initial_page_dir[1024];
void initMemory(uint32_t memhigh, uint32_t physicalAllocStart);
void pmm_init(uint32_t memlow, uint32_t memhigh);
void invalidate(uint32_t vaddr);