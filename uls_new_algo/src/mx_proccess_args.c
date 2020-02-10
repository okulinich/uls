#include "./uls.h"

static int sort_cmd_args(char ***args, char *argv[], char **flags, int size, int *invalid_names) {
    int num_of_files = 0;

    *args = mx_sort_array_of_strings(argv, size);
    num_of_files = mx_move_file_names(*args, size, flags, invalid_names);             //malloc error here!
    if(mx_if_flag_activated('S', flags)) {
        mx_sort_args_by_size(*args, num_of_files);
        mx_sort_args_by_size(&(*args)[num_of_files], size - num_of_files);
    }
    else if(mx_if_flag_activated('t', flags)) {
        if(mx_if_flag_activated('u', flags)) {
            mx_sort_args_by_atime(*args, num_of_files);
            mx_sort_args_by_atime(&(*args)[num_of_files], size - num_of_files);
        }
        else {
            mx_sort_args_by_time(*args, num_of_files);
            mx_sort_args_by_time(&(*args)[num_of_files], size - num_of_files);
        }
    }
    else {
        mx_sort_args(*args, num_of_files);
        mx_sort_args(&(*args)[num_of_files], size - num_of_files);
    }
    return num_of_files;
}

void mx_proccess_args(int num_of_argc, int size, char *argv[], char **flags) {
    DIR *dir;
    char *abs_path = NULL;
    char **arguments = NULL;
    int num_of_files = 0;
    int invalid_names = 0;
    bool flag = false;

    num_of_files = sort_cmd_args(&arguments, argv, flags, num_of_argc, &invalid_names);       //causes malloc error
    if(num_of_files >= 1) {
        mx_proccess_files_separately(arguments, num_of_files, flags);                 //causes segmentation fault in case ./uls -l ~ / /tmp
        if(num_of_argc > num_of_files)
            mx_printchar('\n');
    }
    // /*////////DEBUG///////*/////////////////////////////////////////
    // /**/    printf("\nNum of argc = %d\n", num_of_argc);
    // /**/    printf("Num of files = %d\n", num_of_files);
    // /**/    printf("Invalid names: %d\n", invalid_names);
    // /**/    printf("\nFIles: \t");
    // /**/    for(int i = 0; i < num_of_files; i++)
    // /**/        if(arguments[i])
    // /**/            printf("%s\t", arguments[i]);
    // /**/    printf("\nFolders: \t");
    // /**/    for(int i = num_of_files; i < num_of_argc; i++)
    // /**/        if(arguments[i])
    // /**/            printf("%s\t", arguments[i]);
    // /*/////////////////////*///////////////////////////////////////
    for(int j = num_of_files; j < num_of_argc; j++) {
        abs_path = get_abs_path(arguments[j]);
        dir = opendir(abs_path);
        //printf("cur j = %i\t value = %i\n", j, num_of_argc - invalid_names);
        if(j < num_of_argc - invalid_names - 1)
            flag = true;
        else
            flag = false;
        mx_choose_output_order(dir, flags, num_of_argc, arguments[j], flag);
        if(dir)
            closedir(dir);
    }
    mx_del_array_of_strings(arguments, num_of_argc);                              //causes malloc error
}

void mx_choose_output_order(DIR *dir, char **flags, int num_of_argc, char *argument, bool flag) {
    if(!dir && errno == 13) {
        if(num_of_argc > 1) {
            mx_printstr(argument);
            mx_printstr(":\n");
        }
        mx_per_den(argument);
            if(flag)
                mx_printchar('\n');
        if(num_of_argc == 1)
            exit(1);
    }
    else if(dir) {
        if(num_of_argc > 1 && !((mx_if_flag_activated('l', flags)) && mx_if_arg_is_link(argument)))
            mx_print_folder_name(argument, 0);
        if(mx_if_flag_activated('R', flags))
            mx_recursion(dir, flags, argument);
        else if(!(mx_if_flag_activated('l', flags) && mx_if_arg_is_link(argument)))
            mx_proccess_dir(dir, flags, argument);
        if(flag)
            mx_printchar('\n');
    }
}

char *get_abs_path(char *path) {
    char *new_path;
    char buff[256];

    if(path[0] == '/')      //root dir
        return path;
    new_path = getcwd(buff, 256);           //The getcwd() function copies the absolute pathname of the current working directory
    mx_strcat(new_path, "/");
    mx_strcat(new_path, path);
    return new_path;
}

static bool fill_stat_info_or_not(char **flags) {
    if (mx_if_flag_activated('l', flags) || mx_if_flag_activated('S', flags) ||
        mx_if_flag_activated('t', flags) || mx_if_flag_activated('i', flags) ||
        mx_if_flag_activated('G', flags))
        return true;
    else
        return false;
}

static void format_output(t_current_dir *head, char **flags, bool flag_l, t_spaces max, bool print_total, bool new_line_multi) {
    if(mx_if_flag_activated('1', flags))
        mx_print_in_one_column(head, flags);
    else if(mx_if_flag_activated('l', flags)) {
        if(print_total && mx_find_list_size(head) > 0) {
            mx_printstr("total ");
            mx_printint(max.total);
            mx_printchar('\n');
        }
        mx_long_format_output(head, flags, max);
    }
    else if(isatty(1)) {
        mx_multicol_output(head, flags, max);
    }
    else {
        mx_print_in_one_column(head, flags);
    }
}

void mx_proccess_dir(DIR *dir, char **flags, char *dir_name) {
    struct dirent *entry;
    t_current_dir *head = NULL;
    t_spaces max;
    blkcnt_t total = 0;
    bool flag_l = fill_stat_info_or_not(flags);

    mx_set_spaces_zero(&max);
    for(int i = 0; (entry = readdir(dir)) != NULL; i++) {
        if(mx_if_flag_activated('A', flags) && !mx_if_flag_activated('a', flags) && (mx_strcmp(entry->d_name, ".") == 0 || mx_strcmp(entry->d_name, "..") == 0))
            continue;
        else if(entry->d_name[0] == '.' && !mx_if_flag_activated('a', flags) && !mx_if_flag_activated('A', flags))
            continue;
        mx_push_front_dir(entry->d_name, &head, dir_name);
        if(flag_l) {
            mx_fill_stat_info(head->name, head, dir_name, flags);  //функція що заносить в список додаткову інфу про файли
            mx_count_total(head, flags, &max);
        }
        if(mx_strlen(head->name) > max.longest_name)
            max.longest_name = mx_strlen(head->name);
        head->stat_filled = flag_l;
    }
    mx_sort_list_dir(head, flags);
    format_output(head, flags, flag_l, max, true, false);
    mx_del_list_dir(head);
}

void mx_recursion(DIR *dir, char **flags, char *dir_name) {
    struct dirent *entry;
    DIR *directory;
    t_current_dir *head = NULL;
    t_current_dir *root = NULL;
    t_spaces max;
    blkcnt_t total = 0;
    bool flag_l = fill_stat_info_or_not(flags);
    char *path = NULL;
    char *rel_path = NULL;

    if(flag_l)
        mx_set_spaces_zero(&max);
    for(int i = 0; (entry = readdir(dir)) != NULL; i++) {
        if(mx_if_flag_activated('A', flags) && !mx_if_flag_activated('a', flags) && (mx_strcmp(entry->d_name, ".") == 0 || mx_strcmp(entry->d_name, "..") == 0))
            continue;
        else if(entry->d_name[0] == '.' && !mx_if_flag_activated('a', flags) && !mx_if_flag_activated('A', flags))
            continue;
        mx_push_front_dir(entry->d_name, &head, dir_name);
        if(flag_l) {
            mx_fill_stat_info(head->name, head, dir_name, flags);  //функція що заносить в список додаткову інфу про файли
            mx_count_total(head, flags, &max);
        }
        if(mx_strlen(head->name) > max.longest_name)
            max.longest_name = mx_strlen(head->name);
        head->stat_filled = flag_l;
    }
    mx_sort_list_dir(head, flags);
    format_output(head, flags, flag_l, max, true, false);
    root = head;
    while(head) {
        if(head->name[0] != '.') {
            if(mx_strcmp(dir_name, "/") != 0)
			    rel_path = mx_strjoin(dir_name, "/");
            else
                rel_path = mx_strdup(dir_name);
            path = mx_strjoin(rel_path, head->name);
			directory = opendir(path);
			if(directory) {
				mx_print_folder_name(path, 1);
				mx_recursion(directory, flags, path);
                closedir(directory);
			}
            free(rel_path);
            free(path);
        }
        head = head->next;
    }
    mx_del_list_dir(root);
}

void mx_proccess_files_separately(char **files, int size, char **flags) {
    struct dirent *entry;
    t_current_dir *head = NULL;
    blkcnt_t total = 0;
    t_spaces max;
    struct stat myCurrentStat;
    DIR *dir;
    char *abs_path = NULL;

    mx_set_spaces_zero(&max);
    for(int i = 0; i < size; i++) {
        abs_path = get_abs_path(files[i]);
        dir = opendir(abs_path);
        // if(mx_if_flag_activated('A', flags) && (mx_strcmp(entry->d_name, ".") == 0 || mx_strcmp(entry->d_name, "..") == 0))          
        //     continue;                                                                                                                //дає segmentation fault
        // else if(entry->d_name[0] == '.' && !mx_if_flag_activated('a', flags) && !mx_if_flag_activated('A', flags))
        //     continue;
        if(!dir && lstat(files[i], &myCurrentStat) != -1) {
            mx_push_front_dir(files[i], &head, ".");
            head->cur_stat = myCurrentStat;
            mx_count_total(head, flags, &max);                                //дає помилку malloc object being freed was not allocated
        }
        else if(mx_if_flag_activated('l', flags) && mx_if_arg_is_link(files[i])) {
            lstat(files[i], &myCurrentStat);
            mx_push_front_dir(files[i], &head, ".");
            head->cur_stat = myCurrentStat;
            mx_count_total(head, flags, &max);
            closedir(dir);
        }
        if(mx_strlen(head->name) > max.longest_name)
            max.longest_name = mx_strlen(head->name);
    }
    mx_sort_in_alphanum(head);
    mx_sort_list_dir(head, flags);
    format_output(head, flags, mx_if_flag_activated('l', flags), max, false, true);
    mx_del_list_dir(head);
}
