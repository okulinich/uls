#include "./libmx.h"

static size_t w_strlen(const char *s) {
    size_t i = 0;

    for (;s[i] != '\0'; i++)
        ;
    return i;
}


char *mx_strndup(const char *s1, size_t n) {
    size_t size = n;
    char *s2 = NULL;

    if (n == 0 || !s1)
        return NULL;
    if (w_strlen(s1) < n)
        size = w_strlen(s1);
    s2 = mx_strnew(size);
    if (s2) {
        mx_strncpy(s2, s1, size);
    }
    return s2;
}
