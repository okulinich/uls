#include "./libmx.h"

char *mx_strnew(const int size) {
    char* res = (char *)malloc(size + 1);
    
    if (res) {
        for (int i = 0; i <= size; i++)
            res[i] = '\0';
        return res;
    }
    else
        return NULL;
}
