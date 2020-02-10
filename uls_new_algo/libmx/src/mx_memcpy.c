#include "./libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    byte *dst_ptr = (byte *) dst;
    byte *src_ptr = (byte *) src;

    for (size_t i = 0; i < n; i++)
        dst_ptr[i] = src_ptr[i];
    return dst;
}
