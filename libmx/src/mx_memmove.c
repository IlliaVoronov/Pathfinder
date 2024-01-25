#include "../inc/libmx.h"
void *mx_memmove(void *dst, const void *src, size_t len)
{
    unsigned char *quant = malloc(len);
    quant = mx_memcpy(quant, src, len);
    dst = mx_memcpy(dst, quant, len);
    free(quant);
    return dst;
}
