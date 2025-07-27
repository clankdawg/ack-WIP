#include "../bootconfig/multiboot.h"
#include "../bootconfig/memory.h"
#include "../stdint/stdint.h"
#include "../stdlib/stdio.h"

void initMemory(struct multiboot_info* bootInfo)
{
    for (int i = 0; i < bootInfo->mmap_length; i += sizeof(struct multiboot_mmap_entry)){
        struct multiboot_mmap_entry *mmmt = (struct multiboot_mmap_entry*)(bootInfo->mmap_addr + i);
        printf("Low addr: %x | High addr: %x | Low Length: %x | High Length: %x | Size: %x | Type: %d\n", mmmt->addr_low, mmmt->addr_high, mmmt->len_low, mmmt->len_high, mmmt->size, mmmt->type);
    }
}
