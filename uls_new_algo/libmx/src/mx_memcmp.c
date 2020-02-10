#include "./libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    byte *s1_ptr = (byte *)s1;
    byte *s2_ptr = (byte *)s2;

    for (size_t i = 0; i < n; i++) {
        if (s1_ptr[i] != s2_ptr[i])
            return s1_ptr[i] - s2_ptr[i];
    }
    return 0;
}
