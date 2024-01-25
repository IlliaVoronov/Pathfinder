#include "../inc/libmx.h"

char *mx_strjoin(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 != NULL)
    {
        int lenth = mx_strlen(s2);
        char *returns = mx_strnew(lenth);
        returns = mx_strdup(s2);
        return returns;
    }
    if (s2 == NULL && s1 != NULL)
    {
        int lenth = mx_strlen(s1);
        char *returns = mx_strnew(lenth);
        returns = mx_strdup(s1);
        return returns;
    }
    if (s1 == NULL && s2 == NULL)
    {
        return NULL;
    }
    else
    {
        int lenth = 0;
        int quant = mx_strlen(s1);
        int atom = mx_strlen(s2);
        lenth = quant + atom;
        char *str = mx_strnew(lenth);
        str = mx_strcat(str, s1);
        str = mx_strcat(str, s2);
        return str;
    }
}
