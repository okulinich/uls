#include "./libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    char* res = NULL;
    int i = 0;
    
    if (!needle || mx_strlen(needle) == 0)
        return (char *)haystack;
    for (int j = 0; haystack[i] != '\0'; i++) {
        if (haystack[i] == needle[j]) {
            if (j == mx_strlen(needle) - 1) {
                res = (char *)&haystack[i - j];
                break;
            }
            j++;
        }
        else
            j = 0;
    }
    return res;
}
