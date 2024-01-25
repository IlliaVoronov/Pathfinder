#include "../inc/libmx.h"
int mx_num_len(int number)
{
    int length = 0;
    while (number)
    {
        number /= 10;
        length++;
    }
    return length;
}
