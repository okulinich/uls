#include "./libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int i = 0;
    for (;s1[i] != '\0'; i++)
        ;
    mx_strcpy(&s1[i], s2);
    return s1;
}
