#include "./libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *head = NULL;

    if (!list)
        return ;
    if (!(*list)) {
        *list = mx_create_node(data);
        (*list)->next = NULL;
    }
    else {
        head = *list;
        while(head->next)
            head = head->next;
        t_list *new_node = mx_create_node(data);
        new_node->next = NULL;
        head->next = new_node;
    }
}
