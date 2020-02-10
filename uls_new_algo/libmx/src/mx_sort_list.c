#include "./libmx.h"

void swap(t_list *a, t_list *b) {
    void *temp = a->data;
    a->data = b->data;
    b->data = temp;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    bool swapped = true;
    t_list *ptr;
    t_list *lptr = NULL;

    if (!lst)
        return NULL;    
    while(swapped) {
        swapped = false;
        ptr = lst;
        while(ptr->next != lptr) {
            if (cmp(ptr->data, ptr->next->data)){
                swap(ptr, ptr->next);
                swapped = true;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    }
    return lst;
}
