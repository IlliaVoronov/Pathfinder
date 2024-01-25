#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex)
{
    if (hex == NULL)
    {
        return 0;
    }
    unsigned long quant = 1, result = 0;
    char *str = (char *)hex;
    char *copiedstr = str;
    while (*str != '\0')
    {
        str++;
    }
    while (str-- != copiedstr)
        if (*str >= '0' && *str <= '9')
        {
            result += (*str - '0') * quant;
            quant *= 16;
        }
        else if (*str >= 'a' && *str <= 'f')
        {
            result += (*str - 'a' + 10) * quant;
            quant *= 16;
        }
        else if (*str >= 'A' && *str <= 'F')
        {
            result += (*str - 'A' + 10) * quant;
            quant *= 16;
        }
        else
        {
            return 0;
        }
    return result;
}
