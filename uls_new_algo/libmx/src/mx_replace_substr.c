#include "./libmx.h"

static char *replace_one_sub(char *new_string, const char *sub, int sub_loc, const char *replace) {
    char *new_s = mx_strnew(mx_strlen(new_string) - mx_strlen(sub) + mx_strlen(replace));
    int i = 0;
    int j = 0;

    for (;i < sub_loc; i++)
        new_s[i] = new_string[i];
    while(replace[j] != '\0')
        new_s[i++] = replace[j++];
    mx_strcpy(&new_s[i], &new_string[sub_loc + mx_strlen(sub)]);
    free(new_string);
    return new_s;
}

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str && sub && replace) {
        char *new_string = mx_strnew(mx_strlen(str));
        int sub_loc = mx_get_substr_index(str, sub);
        
        mx_strcpy(new_string, str);
        while(sub_loc >= 0) {
                new_string = replace_one_sub(new_string, sub, sub_loc, replace);
                sub_loc = mx_get_substr_index(new_string, sub);
        }
        return new_string;
    }
    else
        return NULL;
}
