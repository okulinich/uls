#include "./libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    char *res_str = NULL;

    if (!s1 && !s2)
        return NULL;
    if (!s1 || !s2)
        return !s1 ? mx_strcpy(mx_strnew(mx_strlen(s2)), s2) : 
                     mx_strcpy(mx_strnew(mx_strlen(s1)), s1);
    else {
        res_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
        mx_strcpy(res_str, s1);
        mx_strcpy(&res_str[mx_strlen(s1)], s2);
        return res_str;
    }
}
