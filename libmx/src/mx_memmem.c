#include "./libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    const byte *big_ptr = big;

    if (big_len < little_len || little_len == 0 || big_len == 0)
        return NULL;
    for (size_t i = 0; i < big_len; i++) {
        if (mx_memcmp(&big_ptr[i], little, little_len) == 0) {
            return (void *)&big_ptr[i];
        }
    }
    return NULL;
}
