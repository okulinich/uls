#include "uls.h"

void mx_sort_list_dir(t_current_dir *head, char **flags) {
    if(mx_if_flag_activated('S', flags))
        mx_sort_by_size(head);
    else if(mx_if_flag_activated('t', flags)) {
        if(mx_if_flag_activated('u', flags))
            mx_sort_by_atime(head);
        else
            mx_sort_by_time(head);
    }
    else
        mx_sort_in_alphanum(head);
}

void mx_sort_in_alphanum(t_current_dir *head) {
    t_current_dir *first = head;
    t_current_dir *second = NULL;
    char *temp = NULL;
    struct stat tmp;

    while(first) {
        second = first->next;
        while(second) {
            if(mx_strcmp(first->name, second->name) > 0) {
                temp = second->name;
                tmp = second->cur_stat;
                second->name = first->name;
                second->cur_stat = first->cur_stat;
                first->name = temp;
                first->cur_stat = tmp;
            }
            second = second->next;
        }
        first = first->next;
    }
}

void mx_sort_by_size(t_current_dir *head) {
    t_current_dir *first = head;
    t_current_dir *second = NULL;
    char *temp = NULL;
    struct stat tmp;

    while(first) {
        second = first->next;
        while(second) {
            if(first->cur_stat.st_size <= second->cur_stat.st_size) {
                temp = second->name;
                tmp = second->cur_stat;
                second->name = first->name;
                second->cur_stat = first->cur_stat;
                first->name = temp;
                first->cur_stat = tmp;
            }
            second = second->next;
        }
        first = first->next;
    }
}

void mx_sort_by_time(t_current_dir *head) {
    t_current_dir *first = head;
    t_current_dir *second = NULL;
    char *temp = NULL;
    struct stat tmp;

    while(first) {
        second = first->next;
        while(second) {
            if(first->cur_stat.st_mtimespec.tv_sec <= second->cur_stat.st_mtimespec.tv_sec) {
                temp = second->name;
                tmp = second->cur_stat;
                second->name = first->name;
                second->cur_stat = first->cur_stat;
                first->name = temp;
                first->cur_stat = tmp;
            }
            second = second->next;
        }
        first = first->next;
    }
}

void mx_sort_by_atime(t_current_dir *head) {
    t_current_dir *first = head;
    t_current_dir *second = NULL;
    char *temp = NULL;
    struct stat tmp;

    while(first) {
        second = first->next;
        while(second) {
            if(first->cur_stat.st_atimespec.tv_sec <= second->cur_stat.st_atimespec.tv_sec) {
                temp = second->name;
                tmp = second->cur_stat;
                second->name = first->name;
                second->cur_stat = first->cur_stat;
                first->name = temp;
                first->cur_stat = tmp;
            }
            second = second->next;
        }
        first = first->next;
    }
}

void mx_sort_args_by_size(char **names, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - i - 1; j++) {
                struct stat myCurrentStat1;
                int a = lstat(names[j], &myCurrentStat1);

                struct stat myCurrentStat2;
                int b = lstat(names[j + 1], &myCurrentStat2);

                if(a > 0 && b > 0 && myCurrentStat1.st_size < myCurrentStat2.st_size)
                    swap_strings(&names[j], &names[j + 1]);

        }
    }

}

void mx_sort_args_by_time(char **names, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
                struct stat myCurrentStat1;
                int a = lstat(names[j], &myCurrentStat1);

                struct stat myCurrentStat2;
                int b = lstat(names[j + 1], &myCurrentStat2);

                if(a > 0 && b > 0 && (myCurrentStat1.st_mtimespec.tv_sec) < (myCurrentStat2.st_mtimespec.tv_sec))
                    swap_strings(&names[j], &names[j + 1]);

        }
    }
}


void mx_sort_args_by_atime(char **names, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
                struct stat myCurrentStat1;
                int a = lstat(names[j], &myCurrentStat1);

                struct stat myCurrentStat2;
                int b = lstat(names[j + 1], &myCurrentStat2);

                if(a > 0 && b > 0 && (myCurrentStat1.st_atimespec.tv_sec) < (myCurrentStat2.st_atimespec.tv_sec))
                    swap_strings(&names[j], &names[j + 1]);

        }
    }
}