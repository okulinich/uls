#include "./libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int res = -1;

    if (!(str && sub))
        res = -2;
    else {
        int i = 0;
        for (int j = 0; str[i] != '\0'; i++) {
            if (str[i] == sub[j]) {
                if (j == mx_strlen(sub) - 1) {
                    res = i - j;
                    break;
                }
                j++;
            }
        }
    }
    return res;
}
