#include "../inc/libmx.h"

char *mx_strcat(char *s1, const char *s2)
{
    char *quant = s1 + mx_strlen(s1);
    
    while (*s2 != '\0')
    {
        *quant++ = *s2++;
    }
    *quant = '\0';
    return s1;
}
