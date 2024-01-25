#include "../inc/libmx.h"

int mx_list_size(t_list *head)
{
    int num = 0;
    t_list *quant = head;
    while (quant != NULL)
    {
        quant = quant->next;
        num++;
    }
    return num;
}
