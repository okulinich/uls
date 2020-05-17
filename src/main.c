#include "uls.h"
//The ls utility exits 0 on success, and >0 if an error occurs.
int main(int argc, char *argv[]) {
    int i = 1;      //лічильник для роботи з аргументами командної строки
    char **flags = mx_fill_flag_arr();
    int num_of_files = 1;

    if(argc > 1) {
        num_of_files = mx_parse_flags(&i, flags, argc, argv);
        if(num_of_files == 0) {
            argv[0] = ".";
            num_of_files = 1;
            i = 0;
        }
        else if(num_of_files < 0)
            exit(1);
    }
    else {
        i = 0;
        argv[0] = ".";
    }
    mx_proccess_args(num_of_files, argc, &argv[i], flags);
    mx_del_flags(flags);
    //system("leaks -q uls");
    exit(0);
}
