#include "../stdint/stdint.h"

struct multiboot_aout_symbol_table
{
    uint32_t tabsize;  // size of the symbol table
    uint32_t strsize;  // size of the string table
    uint32_t addr;     // address of the symbol table
    uint32_t reserved; // reserved, must be zero
};

struct multiboot_elf_section_header_table
{
    uint32_t num;   // number of sections
    uint32_t size;  // size of each section header
    uint32_t addr;  // address of the section headers
    uint32_t shndx; // section header string table index
};

struct multiboot_info
{
    uint32_t flags;       // flags indicating which fields are valid
    uint32_t mem_lower;   // lower memory size in KB
    uint32_t mem_upper;   // upper memory size in KB
    uint32_t boot_device; // boot device information
    uint32_t cmdline;     // command line address
    uint32_t mods_count;  // number of modules
    uint32_t mods_addr;   // address of modules
    union
    {
        struct multiboot_aout_symbol_table aout_sym;       // a.out symbol table
        struct multiboot_elf_section_header_table elf_sec; // ELF section header table
    };
    uint32_t mmap_length;       // length of memory map
    uint32_t mmap_addr;         // address of memory map
    uint32_t drives_length;     // length of drives
    uint32_t drives_addr;       // address of drives
    uint32_t config_table;      // address of configuration table
    uint32_t boot_loader_name;  // address of boot loader name
    uint32_t apm_table;         // address of APM table
    uint32_t vbe_control_info;  // address of VBE control information
    uint32_t vbe_mode_info;     // address of VBE mode information
    uint16_t vbe_mode;          // VBE mode number
    uint16_t vbe_interface_seg; // VBE interface segment
    uint16_t vbe_interface_off; // VBE interface offset
    uint16_t vbe_interface_len; // VBE interface length
};

struct multiboot_mmap_entry
{
    uint32_t size;
    uint32_t addr_low;
    uint32_t addr_high;
    uint32_t len_low;
    uint32_t len_high;
#define MULTIBOOT_MEMORY_AVAILABLE 1        // available memory
#define MULTIBOOT_MEMORY_RESERVED 2         // reserved memory
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3 // ACPI reclaimable memory
#define MULTIBOOT_MEMORY_NVS 4              // NVS memory
#define MULTIBOOT_MEMORY_BADRAM 5           // bad RAM
    uint32_t type;                          // type of memory
} __attribute__((packed));