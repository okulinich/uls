#include "./libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    byte *s_ptr = (byte *)s;
    void *c_ptr = NULL;

    for (size_t i = 0; i < n; i++) {
        if (c == s_ptr[i]) {
            c_ptr = &s_ptr[i];
            break;
        }
    }
    return c_ptr;
}
