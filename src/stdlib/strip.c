#include "strip.h"

void strip_char(char *strip, int num, char until_char)
{
    int i = 0;
    int until_index = -1;

    if (until_char != '\0')
    {
        while (strip[i] != '\0')
        {
            if (strip[i] == until_char)
            {
                until_index = i;
                break;
            }
            i++;
        }
    }

    int truncate_at = num;
    if (until_index != -1 && (until_index < num || num <= 0))
    {
        truncate_at = until_index;
    }

    if (truncate_at > 0)
    {
        strip[truncate_at] = '\0';
    }
}
