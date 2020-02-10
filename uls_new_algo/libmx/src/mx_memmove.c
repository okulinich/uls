#include "./libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    byte *dst_ptr = (byte *) dst;
    byte *src_ptr = (byte *) src;
    byte *temp = (byte *)malloc(len);

    mx_memcpy(temp, src_ptr, len);
    mx_memcpy(dst_ptr, temp, len);
    free(temp);
    return dst;
}
