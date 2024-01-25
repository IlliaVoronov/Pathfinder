#include "../inc/libmx.h"

void mx_pop_back(t_list **head)
{
    if (*head == NULL)
    {
        return;
    }
    t_list *quant = *head;
    while (quant->next->next)
    {
        quant = quant->next;
    }
    free(quant->next);
    quant->next = NULL;
    quant = NULL;
}
