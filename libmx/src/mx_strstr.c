#include "../inc/libmx.h"

char *mx_strstr(const char *s1, const char *s2)
{
    char *try1 = (char *)s1;
    char *try2 = (char *)s2;

    if ((!s1) || (!s2))
    {
        return 0;
    }
    if (!mx_strlen(s2))
    {
        return try1;
    }
    while (*try1)
    {
        if (!mx_strncmp(try1, try2, mx_strlen(try2)))
        {
            return try1;
        }
        try1++;
    }
    return 0;
}
