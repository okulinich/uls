#include "./libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const byte *s_ptr = (byte *)s;
    void *c_ptr = NULL;

    if (n == 0 || mx_strlen((const char *)s_ptr) > (int)n)
        return NULL;
    for (int i = (int)n - 1; i >= 0; i--) {
        if (c == s_ptr[i]) {
            c_ptr = (void *)&s_ptr[i];
            return c_ptr;
        }
    }
    return NULL;
}
