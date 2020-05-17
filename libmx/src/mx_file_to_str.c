#include "./libmx.h"

char *mx_file_to_str(const char *file) {
    int fd = open(file, O_RDONLY);
    char *str;
    char buf[] = "a";

    if (fd > 0) {
        if (read(fd, buf, 1) > 0) {
            str = mx_strnew(1);
            str = mx_strjoin(str, buf);
            while(read(fd, buf, 1) > 0)
                str = mx_strjoin(str, buf);
            close(fd);
            return str;
        }
        else
            return NULL;
    }
    return NULL;
}
