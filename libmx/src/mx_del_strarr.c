#include "../inc/libmx.h"
void mx_del_strarr(char ***arr)
{
    if (arr == NULL || *arr == NULL)
    {
        return;
    }
    char **quant = *arr;
    while (*quant)
    {
        mx_strdel(quant);
        quant++;
    }
    free(*arr);
    *arr = NULL;
}

