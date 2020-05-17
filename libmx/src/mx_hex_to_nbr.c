#include "./libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long res = 0;
    unsigned long base = 1;

    if (hex) {
        for (int i = mx_strlen(hex) - 1; i >= 0; i--)
            if (hex[i] >= '0' && hex[i] <= '9') {
                res += (hex[i] - 48) * base;
                base *= 16;
            }
            else if (hex[i] >= 'A' && hex[i] <= 'F') {
                res += (hex[i] - 55) * base;
                base *= 16;
            }
            else if (hex[i] >= 'a' && hex[i] <= 'f') {
                res += (hex[i] - 87) * base;
                base *= 16;
            }
    }
    return res;
}
