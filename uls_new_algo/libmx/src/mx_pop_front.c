#include "./libmx.h"

void mx_pop_front(t_list **list) {
    t_list *head = NULL;

    if (!list)
        return ;
    if (!(*list)->next) {
        free(*list);
        *list = NULL;
    }
    else {
        head = *list;
        (*list) = (*list)->next;
        free(head);
        head = NULL;
    }
}
