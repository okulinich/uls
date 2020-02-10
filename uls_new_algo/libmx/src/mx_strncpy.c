#include "./libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    char *dst_copy = dst;
    int i = 0;
    
    for (;i < len && src[i] != '\0'; i++) 
        dst[i] = src[i];
    while(i < len)
        dst[i++] = '\0';
    return dst_copy;
}
