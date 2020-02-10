#include "./libmx.h"

void mx_pop_back(t_list **list) {
    t_list *head = NULL;

    if (!list)
        return ;
    if (!(*list)->next) {
        free(*list);
        *list = NULL;
    }
    else {
        head = *list;
        while(head->next->next)
            head = head->next;
        free(head->next);
        head->next = NULL;
    }
}
