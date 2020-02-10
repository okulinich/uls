#include "uls.h"

bool mx_check_file(char *file_name, char **flags) {
    struct stat cur_file;

    if(lstat(file_name, &cur_file) < 0) {
        return false;
    }
    else
        return true;
}

bool mx_if_arg_is_link(char *name) {
    struct stat cur_file;

    if (lstat(name, &cur_file) == -1)
        return false;
    if (S_ISLNK(cur_file.st_mode))
        return true;
    else
        return false;
}

