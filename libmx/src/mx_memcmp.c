#include "../inc/libmx.h"
int mx_memcmp(const void *s1, const void *s2, size_t n)
{
    if (s1 == NULL && s2 == NULL)
    {
        return 0;
    }
    else if (s1 == NULL)
    {
        return -1;
    }
    else if (s2 == NULL)
    {
        return 1;
    }

    const unsigned char *ptr1 = (const unsigned char *)s1;
    const unsigned char *ptr2 = (const unsigned char *)s2;

    int difference = 0;

    for (size_t i = 0; i < n; i++)
    {
        difference = ptr1[i] - ptr2[i];
        if (difference != 0)
        {
            return difference;
        }
    }

    return 0;
}
