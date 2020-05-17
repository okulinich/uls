#include "./libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    byte *dst_ptr = (byte *) dst;
    byte *src_ptr = (byte *) src;

    for (size_t i = 0; i < n; i++) {
        dst_ptr[i] = src_ptr[i];
        if (dst_ptr[i] == c) {
            return (dst_ptr += (i + 1));
        }
    }
    return NULL;
}
