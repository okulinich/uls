#include "./libmx.h"

int mx_count_words(const char *str, char c) {
    int res = -1;
    int flag = 0;
    int i;

    if (str) {
        int len = mx_strlen(str);
        res = 0;
        for (i = 0; str[i] == c; i++)
            continue;
        for (;i <= len; i++) {
            if ((str[i] == c || str[i] == '\0') && flag == 1) {
                flag = 0;
                res++;
            }
            else if (!(str[i] == c))
                flag = 1;
        }
    }
    return res;
}
