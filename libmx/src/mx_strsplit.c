#include "../inc/libmx.h"

char **mx_strsplit(const char *s, char c)
{
    int length = 0;
    int quant = 0;
    char **arr = NULL;
    if (!s)
    {
        return NULL;
    }
    arr = (char **)malloc((mx_countsletters(s, c) + 1) * sizeof(char *));
    while ((*s) && (*s != '\0'))
    {
        if (*s != c)
        {
            length = mx_countsletters(s, c);
            arr[quant] = mx_strndup(s, length);
            s += length;
            quant++;
            continue;
        }
        s++;
    }
    arr[quant] = NULL;
    return arr;
}

