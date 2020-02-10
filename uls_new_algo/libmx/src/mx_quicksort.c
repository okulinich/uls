#include "./libmx.h"

static void skip_and_swap(char **arr, int *l, int *r, char *pivot, int *sw) {
    char *temp = NULL;

    while(mx_strlen(arr[*l]) < mx_strlen(pivot))
        (*l)++;
    while(mx_strlen(arr[*r]) > mx_strlen(pivot))
        (*r)--;
    if (*l <= *r) {
        temp = arr[*l];
        arr[(*l)++] = arr[*r];
        arr[(*r)--] = temp;
        (*sw)++;
    }
}

int mx_quicksort(char **arr, int left, int right) {
    if(arr) {
        char *pivot = arr[(left + right) / 2];
        int l = left;
        int r = right;
        int swaps = 0;

        while(l <= r)
            skip_and_swap(arr, &l, &r, pivot, &swaps);
        if (left < r)
            mx_quicksort(arr, left, r);
        if (right > l)
            mx_quicksort(arr, l, right);
        return swaps;
    }
    else 
        return -1;
}
