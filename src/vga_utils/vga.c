#include "vga.h"
#include "../stdint/stdint.h"

uint16_t column = 0;                                                           // setup text column (x coordinate)
uint16_t line = 0;                                                             // setup correct line (y coordinate)
uint16_t *const vga = (uint16_t *const)0xC00B8000;                                // VGA buffer memory address
const uint16_t defaultColor = (COLOR8_LIGHT_GREY << 8) | (COLOR8_BLACK << 12); // setting colors
uint16_t currentColor = defaultColor;                                          // setting current color

void Reset()
{
    line = 0;
    column = 0;
    currentColor = defaultColor;

    for (uint16_t y = 0; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            vga[y * width + x] = ' ' | defaultColor; // for every x and y coordinate set it to blank char and defaultColor
        }
    }
}

void newLine()
{
    if (line < height - 1)
    {
        line++; // increment line
        column = 0;
    }
    else
    {
        scrollUp(); // or scroll up
        column = 0;
    }
}

void scrollUp()
{
    for (uint16_t y = 1; y < height; y++)
    {
        for (uint16_t x = 0; x < width; x++)
        {
            vga[(y - 1) * width + x] = vga[y * width + x]; // shift vga text up
        }
    }

    for (uint16_t x = 0; x < width; x++)
    {
        vga[(height - 1) * width + x] = ' ' | currentColor; // then discard the line that goes out of the screen
    }
}

void print(const char *s)
{
    while (*s)
    {
        switch (*s)
        {
        case '\n':
            newLine();
            break;
        case '\r': // IF special character do these cases
            column = 0;
            break;
        case '\b':
            if (column == 0 && line != 0)
            {
                line--;
                column = width;
            }
            vga[line * width + (--column)] = ' ' | currentColor;
            break;
        case '\t':
            if (column == width)
            {
                newLine();
            }
            uint16_t tabLen = 4 - (column % 4);
            while (tabLen != 0)
            {
                vga[line * width + (column++)] = ' ' | currentColor;
                tabLen--;
            }
            break;
        default:
            if (column == width)
            {
                newLine();
            }

            vga[line * width + (column++)] = *s | currentColor; //  put character to the vga buffer
            break;
        }
        s++; // increment string pointer
    }
}