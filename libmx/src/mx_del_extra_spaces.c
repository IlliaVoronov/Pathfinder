#include "../inc/libmx.h"
char *mx_del_extra_spaces(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    int len = mx_strlen(str);
    int start = 0, end = len - 1;

    while (start < len && mx_isspace(str[start]))
    {
        start++;
    }

    while (end >= 0 && mx_isspace(str[end]))
    {
        end--;
    }

    if (start > end)
    {
        return NULL;
    }

    int result_len = end - start + 1;
    char *result = (char *)malloc(result_len + 1);

    if (result == NULL)
    {
        return NULL;
    }

    int i, j = 0;

    for (i = start; i <= end; i++)
    {
        if (mx_isspace(str[i]))
        {
            if (j > 0 && !mx_isspace(result[j - 1]))
            {
                result[j] = ' ';
                j++;
            }
        }
        else
        {
            result[j] = str[i];
            j++;
        }
    }


    result[j] = '\0';

    return result;
}
