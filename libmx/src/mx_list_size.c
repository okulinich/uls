#include "./libmx.h"

int mx_list_size(t_list *list) {
    t_list *head = list;
    int size = 0;

    while (head) {
        size++;
        head = head->next;
    }
    return size;
}
