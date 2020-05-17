#include "libmx.h"

void mx_remember_the_least(int index, char **str_to_write) {
    char *part = mx_strnew(mx_strlen(*str_to_write) - index + 1);

    mx_strcpy(part, &(*str_to_write)[index + 1]);
    mx_strdel(str_to_write);
    *str_to_write = mx_strnew(mx_strlen(part));
    mx_strcpy(*str_to_write, part);
    mx_strdel(&part);
}
