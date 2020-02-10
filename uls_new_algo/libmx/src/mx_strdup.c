#include "./libmx.h"

char *mx_strdup(const char *s1) {
    char *res = NULL;
    char *s2 = (char *)malloc(mx_strlen(s1) + 1);
    
    if(s2)
        res = mx_strcpy(s2, s1);
    else 
        res = NULL;
    return res;
}
