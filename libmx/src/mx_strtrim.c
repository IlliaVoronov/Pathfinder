#include "../inc/libmx.h"
char *mx_strtrim(const char *str)
{
    int second = mx_strlen(str);
    int first = 0;
    int quant = 0;
    if (str != NULL)
    {
        while (mx_isspace(str[quant]))
        {
            first++;
            quant++;
        }
        while (mx_isspace(str[second - 1]))
        {
            second--;
        }
        char *new = mx_strnew(second - first);
        for (int i = first, j = 0; i < second; i++)
        {
            new[j++] = str[i];
        }
        return new;
    }
    return NULL;
}
