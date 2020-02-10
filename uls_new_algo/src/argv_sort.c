#include "uls.h"

void swap_strings(char **a, char **b) {
    char *temp = mx_strdup(*a);

    //printf("\nSwapping %s and %s\n", *a, *b);
    free(*a);
    *a = mx_strdup(*b);
    free(*b);
    *b = mx_strdup(temp);
    free(temp);
}

char **mx_sort_array_of_strings(char **array, int size) {
    char **temp = (char **)malloc(sizeof(char *) * size);

    for(int i = 0; i < size; i++)
        temp[i] = mx_strdup(array[i]);
    return temp;
}

void mx_sort_args(char **array, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(mx_strcmp(array[j], array[j + 1]) > 0)
                swap_strings(&array[j], &array[j + 1]);
        }
    }
}

void mx_del_array_of_strings(char **array, int size) {
    for(int i = 0; i < size; i++)
        free(array[i]);
    free(array);
}


int mx_move_file_names(char **array, int size, char **flags, int *invalid_names) {
    int j = 0;
    DIR *dir;
    int num_of_files = 0;

    for(int i = 0; i < size; i++) {
        dir = opendir(array[i]);
        //printf("\n%s -> %d\n", array[i], dir);
        if(dir) {
            if(mx_if_flag_activated('l', flags) && mx_if_arg_is_link(array[i])) {
                if(i != j)
                    swap_strings(&array[i], &array[j]);
                num_of_files++;
                j++;
            }
            closedir(dir);
        }
        else if(!dir && errno == 13) {
            errno = 0;
        }
        else {
            if(mx_check_file(array[i], flags)) {
                if(i != j)
                    swap_strings(&array[i], &array[j]);
                num_of_files++;
                j++;
            }
            else if(mx_strcmp(array[i], "--") != 0) {
                (*invalid_names)++;
                mx_invalid_name(array[i]);
            }
        }
    }
    return num_of_files;
}
