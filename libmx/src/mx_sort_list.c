#include "../inc/libmx.h"

bool cmp(void *a, void *b)
{
    if (mx_new_strcmp((char *)(a), (char *)(b)) > 0)
        return true;
    return false;
}
t_list *mx_sort_list(t_list *head, bool (*cmp)(void *, void *))
{
    if (!head)
    {
        return NULL;
    }

    for (t_list *i = head; i->next != NULL; i = i->next)
    {
        t_list *quant = i;
        for (t_list *j = i->next; j != NULL; j = j->next)
        {
            if (cmp(quant->data, j->data))
            {
                quant = j;
            }
        }
        void *time = quant->data;
        quant->data = i->data;
        i->data = time;
    }
    return head;
}
