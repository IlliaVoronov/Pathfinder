#include "../inc/libmx.h"
void *mx_realloc(void *ptr, size_t size)
{
    size_t quant = malloc_size(ptr);
    if (!size)
    {
        free(ptr);
        return NULL;
    }
    else if (!ptr)
    {
        return malloc(size);
    }
    else if (size <= quant)
    {
        return ptr;
    }
    void *new_ptr = malloc(size);
    if (new_ptr)
    {
        mx_memcpy(new_ptr, ptr, quant);
        free(ptr);
    }
    return new_ptr;
}
