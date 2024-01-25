#include "../inc/libmx.h"

void mx_push_front(t_list **head, void *data)
{
    t_list *quant = *head;
    *head = mx_create_node(data);
    (*head)->next = quant;
}
