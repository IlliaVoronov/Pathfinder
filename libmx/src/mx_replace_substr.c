#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace)
{
    if (str == NULL || sub == NULL || replace == NULL)
    {
        return NULL;
    }

    int str_len = mx_strlen(str);
    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);

    char *result = mx_strnew(str_len);

    if (result == NULL)
    {
        return NULL;
    }

    int i = 0;
    while (i < str_len)
    {

        if (mx_strncmp(&str[i], sub, sub_len) == 0)
        {

            mx_memcpy(&result[mx_strlen(result)], replace, replace_len);
            i += sub_len;
        }
        else
        {

            result[mx_strlen(result)] = str[i];
            i++;
        }
    }

    return result;
}
