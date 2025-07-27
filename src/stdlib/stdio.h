#include "../stdint/stdint.h"

void putc(char c);
void puts(const char *str);
void printf(const char *fmt, ...);
void printf_number_simple(uint32_t num, int base, bool is_signed);
void printf_number_simple_upper(uint32_t num, int base, bool is_signed);