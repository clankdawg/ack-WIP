#pragma once
#include "../stdint/stdint.h"

#define COLOR8_BLACK 0
#define COLOR8_WHITE 7

#define width 80
#define height 25

void print(const char *s);
void scrollUp();
void newLine();
void Reset();
