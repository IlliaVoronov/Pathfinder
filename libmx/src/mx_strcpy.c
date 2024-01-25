#include "../inc/libmx.h"
char *mx_strcpy(char *dst, const char *src)
{
    int quant = 0;
    while (src[quant] != '\0')
    {
        dst[quant] = src[quant];
        quant++;
    }
    dst[quant] = '\0';
    return dst;
}
