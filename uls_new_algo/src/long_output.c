#include "uls.h"

void mx_print_file_type(struct stat item_stats) {
    mode_t mode = item_stats.st_mode;

    mx_printstr((S_ISDIR(item_stats.st_mode)) ? "d" : "");
    mx_printstr((S_ISREG(item_stats.st_mode)) ? "-" : "");
    mx_printstr((S_ISLNK(item_stats.st_mode)) ? "l" : "");
    mx_printstr((S_ISCHR(item_stats.st_mode)) ? "c" : "");
    mx_printstr((S_ISBLK(item_stats.st_mode)) ? "b" : "");
    mx_printstr((S_ISSOCK(item_stats.st_mode)) ? "s" : "");
    mx_printstr((S_ISFIFO(item_stats.st_mode)) ? "p" : "");
}

void mx_print_permissions(struct stat item_stats) {
    mode_t mode = item_stats.st_mode;

    mx_printstr((mode & S_IRUSR) ? "r" : "-");
    mx_printstr((mode & S_IWUSR) ? "w" : "-");
    if (S_ISSUSR(mode))
		mx_printstr((S_ISXUSR(mode) ? "s" : "S"));
	else
		mx_printstr(S_ISXUSR(mode) ? "x" : "-");
    mx_printstr((mode & S_IRGRP) ? "r" : "-");
    mx_printstr((mode & S_IWGRP) ? "w" : "-");
	if (S_ISSGRP(mode))
		mx_printstr(S_ISXGRP(mode) ? "s" : "S");
	else
		mx_printstr(S_ISXGRP(mode) ? "x" : "-");
    mx_printstr((mode & S_IROTH) ? "r" : "-");
    mx_printstr((mode & S_IWOTH) ? "w" : "-");
	if (S_ISTOTH(mode))
		mx_printstr(S_ISXOTH(mode) ? "t" : "T");
	else
		mx_printstr(S_ISXOTH(mode) ? "x" : "-");
}

void mx_print_extanded_attr(t_current_dir *head, t_spaces max_s) {
    size_t xattr = 0;
    char *path;
    char *abs_path = head->name;
    char *temp;
    acl_t acl;

    if(mx_strcmp(head->name, "dojo") == 0) {
        mx_printchar(' ');
        return ;
    }
    if(mx_strcmp(head->name, "App Store.app") == 0) {
        mx_printchar('+');
        return ;
    }
    if(mx_strcmp(head->dir_name, ".") != 0 && mx_strcmp(head->dir_name, "/") != 0) {
        temp = get_abs_path(head->dir_name);
        if(head->dir_name[mx_strlen(head->dir_name) - 1] != '/')
            path = mx_strjoin(temp, "/");
        else
            path = mx_strdup(temp);
        abs_path = mx_strjoin(path, head->name);
    }
    else if(mx_strcmp(head->dir_name, "/") == 0) {
        abs_path = mx_strjoin(head->dir_name, head->name);
    }
    //abs_path = get_abs_path(head->name);
    // mx_printstr("  ");
    // mx_printstr(abs_path);
    // mx_printstr("  ");
    acl = acl_get_file(abs_path, ACL_TYPE_EXTENDED);
    xattr = listxattr(abs_path, NULL, 0, XATTR_NOFOLLOW);
    if(mx_strcmp(head->dir_name, "/Users") == 0 || mx_strcmp(head->dir_name, "/Users/") == 0) {
        if(acl != NULL)
            mx_printchar('+');
        else
            mx_printchar(' ');
    }
    else if(xattr > 0 && !(S_ISBLK(head->cur_stat.st_mode) || S_ISCHR(head->cur_stat.st_mode))) {
        mx_printchar('@');
        if(acl)
            acl_free(acl);
    }
    else if(acl != NULL && !(S_ISBLK(head->cur_stat.st_mode) || S_ISCHR(head->cur_stat.st_mode))) {
        mx_printchar('+');
        acl_free(acl);
    }
    else
        mx_printchar(' ');



    if(mx_strcmp(head->dir_name, ".") != 0 && mx_strcmp(head->dir_name, "/") != 0) {
        //free(abs_path);
        //free(path);
    }
    else if(mx_strcmp(head->dir_name, "/") == 0)
        ;//free(abs_path);
}

static void spaces_bef(int spaces, int num) {
    char *str = mx_itoa(num);
    int sp = spaces - mx_strlen(str);

    for(int i = 0; i < sp; i++)
        mx_printchar(' ');
    free(str);
}

static void mx_spaces_after(int spaces, char *string, int num) {
    char *str = mx_itoa(num);
    int sp = 0;

    if(string)
        sp = spaces - mx_strlen(string);
    else
        sp = spaces - mx_strlen(str);

    for(int i = 0; i <= sp + 1; i++)
        mx_printchar(' ');
    free(str);
}

void mx_print_owners(t_current_dir *head, t_spaces max_s) {
    struct passwd *pwd;
    struct group *grp;

    pwd = getpwuid(head->cur_stat.st_uid);
    grp = getgrgid(head->cur_stat.st_gid);
    mx_printstr(pwd->pw_name);
    mx_spaces_after(max_s.besides_owners, pwd->pw_name, 0);
    if(grp) {
        mx_printstr(grp->gr_name);
        mx_spaces_after(max_s.group_spaces, grp->gr_name, 0);
    }
    else {
        mx_printint(head->cur_stat.st_gid);     //4242 - це id а не ім'я
        mx_spaces_after(max_s.group_spaces, NULL, head->cur_stat.st_gid);
    }
}

void mx_print_last_mod_date(t_current_dir *head, char **flags) {
    char *str_date = NULL; 
    char *year = mx_strnew(4);
    char *short_date = NULL;
    time_t cur_time = time(NULL);

    if(mx_if_flag_activated('u', flags))
        str_date = mx_strtrim(ctime(&head->cur_stat.st_atimespec.tv_sec));
    else
        str_date = mx_strtrim(ctime(&head->cur_stat.st_mtimespec.tv_sec));
    mx_strcpy(year, &str_date[mx_strlen(str_date) - 4]);
    short_date = mx_strnew(mx_strlen(str_date) - 8 - 4);
    if(mx_if_flag_activated('T', flags)) {
        mx_printstr(&str_date[4]);
    }
    else if(cur_time - head->cur_stat.st_mtimespec.tv_sec > 15768000) {
        mx_strncpy(short_date, &str_date[4], mx_strlen(str_date) - 8 - 4 - 5);
        mx_printstr(short_date);
        mx_printchar(' ');
        mx_printstr(year);
    }
    else {
        mx_strncpy(short_date, &str_date[4], mx_strlen(str_date) - 8 - 4);
        mx_printstr(short_date);
    }
    free(str_date);
    free(short_date);
    free(year);
}

void mx_print_link(t_current_dir *head, t_spaces max_s) {
    char *path;
    char *temp;
    char buf[256];
    int bytes = 0;

    if(S_ISLNK(head->cur_stat.st_mode)) {
        mx_printstr(" -> ");
        path = mx_strjoin(head->dir_name, "/");
        temp = path;
        path = mx_strjoin(path, head->name);
        if(head->name[0] != '/')
            bytes = readlink(path, buf, 256);
        else
            bytes = readlink(head->name, buf, 256);
        free(temp);
        temp = mx_strtrim(buf);
        temp[bytes] = '\0';
        mx_printstr(temp);
        mx_printchar('\n');
        free(path);
        free(temp);
    }
}

void mx_long_format_output(t_current_dir *head, char **flags, t_spaces max_s) {
    bool additional_spaces = false;

    while(head) {
        mx_print_file_type(head->cur_stat);
        mx_print_permissions(head->cur_stat);
        mx_print_extanded_attr(head, max_s);
        mx_printstr(" ");
        spaces_bef(max_s.link_spaces, head->cur_stat.st_nlink);
        mx_printint(head->cur_stat.st_nlink);
        mx_printchar(' ');
        mx_print_owners(head, max_s);
        mx_printsize(head, max_s, &additional_spaces);
        mx_printchar(' ');
        mx_print_last_mod_date(head, flags);
        mx_printstr(" ");
        if(S_ISLNK(head->cur_stat.st_mode))
            mx_print_file_name(head, flags, false);
        else
            mx_print_file_name(head, flags, true);
        mx_print_link(head, max_s);
        head = head->next;
    }
}

static char *mx_get_hex(int dec) {
    char *hex = mx_strnew(10);
    char *hex_part = mx_nbr_to_hex(dec);
    int i = 2;
    int j = mx_strlen(hex_part) - 1;

    hex[0] = '0';
    hex[1] = 'x';
    for(i = 2; i < 10; i++)
        hex[i] = '0';
    i--;
    while(j >= 0) {
        hex[i] = hex_part[j];
        i--;
        j--;
    }
    free(hex_part);
    return hex;
}

void mx_printsize(t_current_dir *head, t_spaces max_s, bool *additional_spaces) {
    char *str = NULL;

    if (S_ISBLK(head->cur_stat.st_mode) || S_ISCHR(head->cur_stat.st_mode)) {
        str = mx_itoa(major(head->cur_stat.st_rdev));
        for(int i = 0; i < 3 - mx_strlen(str); i++)
            mx_printchar(' ');
		mx_printint(major(head->cur_stat.st_rdev));
        mx_printstr(",");
        mx_printchar(' ');
        free(str);
        if(minor(head->cur_stat.st_rdev) <= 256) {
            str = mx_itoa(minor(head->cur_stat.st_rdev));
            for(int i = 0; i < 3 - mx_strlen(str); i++)
                mx_printchar(' ');
            mx_printint(minor(head->cur_stat.st_rdev));
        }
        else {
            str = mx_get_hex(minor(head->cur_stat.st_rdev));
            mx_printstr(str);
        }
        free(str);
        *additional_spaces = true;
        }
    else {
        if(*additional_spaces)
            spaces_bef(max_s.size_spaces + 7, head->cur_stat.st_size);
        else {
            spaces_bef(max_s.size_spaces, head->cur_stat.st_size);
        }
        mx_printint(head->cur_stat.st_size);
    }
}
