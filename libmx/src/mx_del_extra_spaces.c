#include "./libmx.h"

static bool w_isspace(char c) {
    if (c == '\n' || c == '\t' || c == ' ' ||
        c == '\f' || c == '\r' || c == '\v')
        return true;
    return false;
}

static int count_spaces(const char *str) {
    int res = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (w_isspace(str[i]))
            res++;
    }
    return res;
}

static int count_words_ver2(const char *str) {
    int res = -1;
    int flag = 0;
    int i;

    if (str) {
        int len = mx_strlen(str);
        res = 0;
        for (i = 0; w_isspace(str[i]); i++)
            continue;
        for ( ; i <= len; i++) {
            if ((w_isspace(str[i]) || str[i] == '\0') && flag == 1) {
                flag = 0;
                res++;
            }
            else if (!w_isspace(str[i]))
                flag = 1;
        }
    }
    return res;
}

char *mx_del_extra_spaces(const char *str) {
    if (str) {
        int spaces = count_spaces(str);
        int words = count_words_ver2(str);
        int new_size = mx_strlen(str) - spaces + words - 1;
        char *tr_str = mx_strnew(new_size);

        for (int i = 0, j = 0; str[i] != '\0'; i++)
            if (w_isspace(str[i]))
                continue;
            else {
                while(!w_isspace(str[i]))
                    tr_str[j++] = str[i++];
                tr_str[j++] = ' ';
            }
        tr_str[new_size] = '\0';
        return tr_str;
    }
    else
        return NULL;
}
