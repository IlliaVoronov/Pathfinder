#include "../inc/libmx.h"
void *mx_memrchr(const void *s, int c, size_t n)
{
    if (s == NULL || n == 0)
    {
        return NULL;
    }
    const unsigned char *ptr = (const unsigned char *)s;
    unsigned char target = (unsigned char)c;

    ptr += n - 1;

    for (size_t i = n; i > 0; i--)
    {
        if (*ptr == target)
        {
            return (void *)ptr;
        }
        ptr--;
    }
    return NULL;
}
