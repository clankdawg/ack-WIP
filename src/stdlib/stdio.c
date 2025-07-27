#include "../stdint/stdint.h"
#include "stdio.h"
#include "../vga_utils/vga.h"

void putc(char c)
{
    char str[2] = {c, '\0'};
    print(str);
}

void puts(const char *s)
{
    while (*s)
    {
        putc(*s);
        s++;
    }
}

void printf(const char *fmt, ...)
{
    uint32_t *args = (uint32_t *)((char *)&fmt + sizeof(fmt));
    int arg_index = 0;

    while (*fmt)
    {
        if (*fmt == '%' && *(fmt + 1))
        {
            fmt++;

            switch (*fmt)
            {
            case 'c':
            {
                char c = (char)args[arg_index++];
                putc(c);
                break;
            }
            case 's':
            {
                const char *str = (const char *)args[arg_index++];
                if (str)
                {
                    puts(str);
                }
                else
                {
                    puts("(null)");
                }
                break;
            }
            case 'd':
            case 'i':
            {
                int num = (int)args[arg_index++];
                printf_number_simple(num, 10, true);
                break;
            }
            case 'u':
            {
                uint32_t num = args[arg_index++];
                printf_number_simple(num, 10, false);
                break;
            }
            case 'x':
            {
                uint32_t num = args[arg_index++];
                printf_number_simple(num, 16, false);
                break;
            }
            case 'X':
            {
                uint32_t num = args[arg_index++];
                printf_number_simple_upper(num, 16, false);
                break;
            }
            case '%':
            {
                putc('%');
                break;
            }
            default:
            {
                putc('%');
                putc(*fmt);
                break;
            }
            }
        }
        else
        {
            putc(*fmt);
        }
        fmt++;
    }
}
void printf_number_simple(uint32_t num, int base, bool is_signed)
{
    if (is_signed && (int32_t)num < 0)
    {
        putc('-');
        num = -(int32_t)num;
    }

    if (num == 0)
    {
        putc('0');
        return;
    }

    char buffer[32];
    int pos = 0;
    const char digits[] = "0123456789abcdef";

    while (num > 0)
    {
        buffer[pos++] = digits[num % base];
        num /= base;
    }

    for (int i = pos - 1; i >= 0; i--)
    {
        putc(buffer[i]);
    }
}

void printf_number_simple_upper(uint32_t num, int base, bool is_signed)
{
    if (is_signed && (int32_t)num < 0)
    {
        putc('-');
        num = -(int32_t)num;
    }

    if (num == 0)
    {
        putc('0');
        return;
    }

    char buffer[32];
    int pos = 0;
    const char digits[] = "0123456789ABCDEF";

    while (num > 0)
    {
        buffer[pos++] = digits[num % base];
        num /= base;
    }

    for (int i = pos - 1; i >= 0; i--)
    {
        putc(buffer[i]);
    }
}