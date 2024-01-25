#include "../inc/libmx.h"

void mx_push_back(t_list **head, void *data)
{
    if (!*head)
    {
        *head = mx_create_node(data);
        return;
    }
    t_list *temp = *head;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = mx_create_node(data);
}
