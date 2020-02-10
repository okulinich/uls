#include "./libmx.h"

static bool mx_isspace(char c) {
    if (c == '\n' || c == '\t' || c == ' ' ||
        c == '\f' || c == '\r' || c == '\v')
        return true;
    return false;
}

char *mx_strtrim(const char *str) {
    char *tr_str = NULL;

    if (str) {
        int at_the_begin = 0; //num of space symb
        int at_the_end = 0;
        int size = mx_strlen(str);
        int new_size = 0;

        for (int i = 0; mx_isspace(str[i]); i++)
            at_the_begin++;
        if(at_the_begin == mx_strlen(str))
            return mx_strnew(0);  
        for (int i = size - 1; mx_isspace(str[i]); i--)
            at_the_end++;
        new_size = size - at_the_end - at_the_begin;
        tr_str = mx_strnew(new_size);
        mx_strncpy(tr_str, &str[at_the_begin], new_size);
    }
    return tr_str;
}
