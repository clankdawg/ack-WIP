#include "multiboot.h"
#include "memory.h"
#include "../stdint/stdint.h"
#include "../stdlib/stdio.h"
#include "../vga_utils/util.h"

static uint32_t pageFrameMin;
static uint32_t pageFrameMax;
static uint32_t totalAlloc;

#define NUM_PAGE_DIRS 256
#define NUM_PAGE_FRAMES (0x100000000 / 0x1000 / 8) // 4GB / 4KB pages

uint8_t physicalMemoryBitmap[NUM_PAGE_FRAMES / 8];

static uint32_t pageDirs[NUM_PAGE_DIRS][1024] __attribute__((aligned(4096)));
static uint8_t pageDirsUsed[NUM_PAGE_DIRS];

void invalidate(uint32_t vaddr)
{
    asm volatile("invlpg %0" :: "m"(vaddr));
}


void pmm_init(uint32_t memlow, uint32_t memhigh){
    pageFrameMin = CEIL_DIV(memlow, 0x1000);
    pageFrameMax = memhigh / 0x1000;
    totalAlloc = 0;

    memset(physicalMemoryBitmap, 0, sizeof(physicalMemoryBitmap)); // clear the bitmap

}

void initMemory(uint32_t memhigh, uint32_t physicalAllocStart)
{
    initial_page_dir[0] = 0;
    invalidate(0);
    initial_page_dir[1023] = ((uint32_t) initial_page_dir - KERNEL_START) | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE;
    invalidate(0xFFFFF000); // invalidate the last page directory entry

    pmm_init(physicalAllocStart, memhigh); // initialize physical memory management
    memset(pageDirs, 0, 0x1000 * NUM_PAGE_DIRS); // clear page directory entries
    memset(pageDirsUsed, 0, sizeof(pageDirsUsed)); // clear page directory usage flags
}
