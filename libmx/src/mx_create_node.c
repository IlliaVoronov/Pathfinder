#include "../inc/libmx.h"
t_list *mx_create_node(void *data)
{
    t_list *new_NODE = (t_list *)malloc(16);
    new_NODE->next = NULL;
    new_NODE->data = data;
    return new_NODE;
}
