#include "./libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int res = 0;
    char *next_part = NULL;

    if (!(str && sub))
        res = -1;
    else {
        next_part = (char *)&str[0];
        if (mx_strlen(str) > 0 && mx_strlen(sub) > 0) {
            while((next_part = mx_strstr(next_part, sub)) != NULL) {
                next_part++;
                res++;
            }
        }
    }
    return res;
}
