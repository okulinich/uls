#include "uls.h"

static void print_spaces(int i) {
    for(int j = 0; j < i; j++)
        mx_printchar(' ');
}

void mx_multicol_output(t_current_dir *head, char **flags, t_spaces max_s) {
    struct winsize w; 
    unsigned int tab_size = 8;
    int list_size = mx_find_list_size(head);
    int cols = 0;
    int rows_in_col = 0;
    t_current_dir *buf;
    int i = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if(max_s.longest_name >= tab_size)
        tab_size = (max_s.longest_name / 8 + 1) * 8;
    cols = w.ws_col / tab_size;
    //printf("longest str = %d\ntab_size = %d\ncols = %d\nlist size = %d\n", max_s.longest_name, tab_size, cols, list_size);
    if(cols <= 1)
        mx_print_in_one_column(head, flags);
    else {
        if(list_size % cols > 0)
            rows_in_col = list_size / cols + 1;
        else
            rows_in_col = list_size / cols;
        //printf("rows in col = %i\n", rows_in_col);
        for(int j = 0; j < rows_in_col; j++) {
            i = j;
            while(mx_get_index_dir(i, head)) {
                buf = mx_get_index_dir(i, head);
                mx_print_file_name(buf, flags, false);
                print_spaces(tab_size - mx_strlen(buf->name));
                i += rows_in_col;
            }
            mx_printchar('\n');
        }
    }
}

