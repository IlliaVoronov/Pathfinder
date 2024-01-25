#include "../inc/libmx.h"
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
    char *dest_ptr = (char *)dst;
    const char *src_ptr = (const char *)src;

    for (size_t i = 0; i < n; i++)
    {
        dest_ptr[i] = src_ptr[i];
    }
    return dst;
}

