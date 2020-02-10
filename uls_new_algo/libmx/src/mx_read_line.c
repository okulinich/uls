#include "libmx.h"

static int check_desc(t_file *f, int d) {
    int i;

    if (d <= 0)
        return -1;
    for (i = 0; i < 256; i++)
        if (f->desc[i] == d)
            return i;
    for (i = 0; f->desc[i] != 0; i++) 
        ;
    f->desc[i] = d;
    return i;
}

static bool write_before_delim(char **lineptr, char delim, char **str_to_write) {
    int index = mx_check_delim(*str_to_write, delim);
    char *temp = NULL;
    char *part = NULL;

    if (index == -1) {
        temp = *lineptr;
        *lineptr = mx_strjoin(*lineptr, *str_to_write);
        mx_strdel(&temp);
        mx_strdel(str_to_write);
        return false;
    }
    part = mx_strnew(index);
    mx_strncpy(part, *str_to_write, index);
    temp = *lineptr;
    *lineptr = mx_strjoin(*lineptr, part);
    mx_strdel(&temp);
    mx_strdel(&part);
    mx_remember_the_least(index, str_to_write);
    return true;
}

static void remember_into_static(char **static_str, char **next_line) {
    *static_str = mx_strnew(mx_strlen(*next_line));
    mx_strcpy(*static_str, *next_line);
    mx_strdel(next_line);
}

static bool check_and_clean(int buf_size, int fd, char **lineptr) {
    if (buf_size <= 0 || fd <= 0)
        return false;
    if (lineptr && *lineptr)
        mx_strdel(lineptr);
    *lineptr = mx_strnew(1);
    return true;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static t_file curr_file;
    int arr[2] = {1, check_desc(&curr_file, fd)};
    char *next_line = NULL;

    if (!check_and_clean(buf_size, fd, lineptr))
        return -1;
    while(arr[0] > 0)
        if (curr_file.str[arr[1]]) {
            if (write_before_delim(lineptr, delim, &curr_file.str[arr[1]]))
                return mx_strlen(*lineptr);
        }
        else {
            next_line = mx_strnew(buf_size);
            arr[0] = read(fd, next_line, buf_size);
            if (write_before_delim(lineptr, delim, &next_line)) {
                remember_into_static(&curr_file.str[arr[1]], &next_line);
                return mx_strlen(*lineptr);
            }
        }
    return arr[0];
}
