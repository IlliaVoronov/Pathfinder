#include "../inc/libmx.h"

char *mx_strdup(const char *str)
{
    int lenth = mx_strlen(str);

    char *result = mx_strnew(lenth);
    
    mx_strcpy(result, str);
    return result;
}
