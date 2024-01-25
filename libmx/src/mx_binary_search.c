#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count)
{
    int quant = 0;
    int start = size - 1;
    int medium;
    if (!*arr)
    {
        return -1;
    }
    else
    {
        while (quant <= start)
        {
            (*count)++;
            medium = (start + quant) / 2;

            if (mx_strcmp(arr[medium], s) == 0)
            {
                return medium;
            }
            else if (mx_strcmp(arr[medium], s) > 0)
            {
                start = medium - 1;
            }
            else
            {
                quant = medium + 1;
            }
        }
        *count = 0;
        return -1;
    }
}

