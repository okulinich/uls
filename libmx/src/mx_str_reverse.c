#include "./libmx.h"

void mx_swapchar(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void mx_str_reverse(char *str) {
    if (str) {
        int i = 0;
        int j = mx_strlen(str) - 1;

        while(i <= j)
            mx_swapchar(&str[i++], &str[j--]);
    }
}
