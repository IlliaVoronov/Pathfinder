#include "../inc/libmx.h"
void mx_str_reverse(char *s)
{
    if (s == NULL)
    {
        return;
    }
    int lenth = mx_strlen(s) - 1;
    if (s)
    {
        for (int quant = 0; quant <= (lenth / 2); quant++)
        {
            mx_swap_char(&s[quant], &s[lenth - quant]);
        }
    }
}

