#include "uls.h"

void mx_printerr(char *str) {
    write(2, str, mx_strlen(str));
}

static void mx_print_err_char(char c) {
    write(2, &c, 1);
}

void mx_invalid_flag(char c) {
    mx_printerr("uls: illegal option -- ");
    mx_print_err_char(c);
    mx_printerr("\n");
}

void mx_usage() {
    mx_printerr("usage: uls [-lRaSt1GAuT] [file ...]\n");
}

void mx_invalid_name(char *file_name) {
    mx_printerr("uls: ");
    mx_printerr(file_name);
    mx_printerr(": No such file or directory\n");
}

static char *get_folder(char *path) {
    char *folder = mx_strnew(mx_strlen(path));
    int j = 0;

    for(int i = mx_strlen(path) - 1; path[i] != '/' && i > 0; i--) {
        folder[j] = path[i];
        j++;
    }
    folder[j] = '\0';
    mx_str_reverse(folder);
    return folder;
}

void mx_per_den(char *path) {
    char *folder = get_folder(path);

    mx_printerr("uls: ");
    mx_printerr(folder);
    mx_printerr(": Permission denied\n");
    free(folder);
}