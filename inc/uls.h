#ifndef ULS_H
#define ULS_H

#include "./libmx/inc/libmx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <errno.h>
#include <string.h>

# define BLUE	"\e[3;34m"
# define RED	"\e[0;31m"
# define MAG	"\e[0;35m"
# define GR		"\e[0;32m"
# define BR		"\e[0;33m"
# define BL_YEL	"\e[0;34;43m"
# define BL_CYN	"\e[0;34;46m"
# define NORM	"\e[0m"
# define GREEN  "\e[30;48;5;2m"
# define REDRED "\e[30;48;5;160m"
# define YELLOW "\e[33m"

#define S_IRUSR 0000400
#define S_IWUSR 0000200
#define S_ISXUSR(m) (m & S_IXUSR)
#define S_IRGRP 0000040
#define S_IWGRP 0000020
#define S_ISXGRP(m) (m & S_IXGRP)
#define S_IROTH 0000004
#define S_IWOTH 0000002
#define S_ISXOTH(m) (m & S_IXOTH)

#define S_ISSUSR(m) (m & S_ISUID)
#define S_ISSGRP(m) (m & S_ISGID)
#define S_ISTOTH(m) (m & S_ISTXT)

#define STDOUT_FILENO 1
#define TIOCGWINSZ _IOR('t', 104, struct winsize)

#define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#define S_ISSOCK(m) (((m) & S_IFMT) == S_IFSOCK)
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)

#define major(x) ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
#define minor(x) ((int32_t)((x) & 0xffffff))

typedef struct s_current_dir {
    char *name;
    struct stat cur_stat;
    char *dir_name;
    bool stat_filled;
    struct s_current_dir *next;
} t_current_dir;

typedef struct s_spaces {
    int link_spaces;
    int size_spaces;
    int owner_spaces;
    int besides_owners;
    int group_spaces;
    int major_spaces;
    int minor_spaces;
    int longest_name;
    blkcnt_t total;
} t_spaces;

//функції для роботи із флагами
char **mx_fill_flag_arr();
bool mx_if_flag_activated(char f, char **flags);
void mx_del_flags(char **flags);
int mx_parse_flags(int *i, char **flags, int argc, char *argv[]);
int mx_is_flag(char c, char **flags);

//опрацювання помилок
void mx_invalid_flag(char c);
void mx_usage();
void mx_invalid_name(char *file_name);
void mx_per_den(char *path);

//основний алгоритм
void mx_proccess_args(int i, int argc, char **argv, char **flags);
char *get_abs_path(char *path);
void mx_proccess_dir();
void mx_choose_output_order(DIR *dir, char **flags, int num_of_argc, char *argument, bool flag);
void mx_recursion(DIR *dir, char **flags, char *dir_name);

//обробка аргументів командної строки
char **mx_sort_array_of_strings(char **argv, int size);
void mx_del_array_of_strings(char **array, int size);
bool mx_check_file(char *file_name, char **flags);
int mx_move_file_names(char **array, int size, char **flags, int *inv_names);
void mx_proccess_files_separately(char **files, int size, char **flags);
bool mx_process_file(char *file_name, char **flags, char *dir_name);

//принти
void mx_print_folder_name(char *name, int num);
void mx_long_format_output(t_current_dir *head, char **flags, t_spaces max_s);
void mx_print_file_name(t_current_dir *head, char **flags, bool flag);
void mx_print_file_type(struct stat item_stats);
void mx_print_permissions(struct stat item_stats);
void mx_print_owners(t_current_dir *head, t_spaces max_s);
void mx_print_last_mod_date(t_current_dir *head, char **flags);
void mx_print_link(t_current_dir *head, t_spaces max_s);
void mx_print_in_columns(t_current_dir *head, int cols, int tab_s, char **f);
void mx_printsize(t_current_dir *head, t_spaces max_s, bool *additional_spaces);
void mx_print_in_one_column(t_current_dir *head, char **flags);
void mx_long_format_output(t_current_dir *head, char **flags, t_spaces max);
void mx_multicol_output(t_current_dir *head, char **flags, t_spaces max_s);

//функції списків
void mx_set_spaces_zero(t_spaces *max);
void mx_push_front_dir(char *name, t_current_dir **head, char *dir_name);
void mx_fill_stat_info(char *name, t_current_dir *cur, char *dir_name, char **flags);
void mx_del_list_dir(t_current_dir *head);
void mx_skip_hidden(t_current_dir **head);
void mx_push_back_dir(t_current_dir **head, t_current_dir *source);
int mx_find_list_size(t_current_dir *head);
void mx_del_list_with_names(t_current_dir *head);
void mx_skip_hidden(t_current_dir **head);
t_current_dir *mx_get_index_dir(int num, t_current_dir *head);

//функції сортування
void mx_sort_list_dir(t_current_dir *head, char **flags);
void mx_sort_in_alphanum(t_current_dir *head);
void mx_sort_by_size(t_current_dir *head);
void mx_sort_by_time(t_current_dir *head);
void mx_sort_args(char **array, int size);
void mx_sort_args_by_size(char **names, int size);
void mx_sort_args_by_time(char **names, int size);
void swap_strings(char **a, char **b);
void mx_sort_args_by_atime(char **names, int size);
void mx_sort_by_atime(t_current_dir *head);

void mx_count_total(t_current_dir *head, char **flags, t_spaces *max_s);

bool mx_if_arg_is_link(char *name);

#endif
