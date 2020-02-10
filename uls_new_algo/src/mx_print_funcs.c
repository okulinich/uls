#include "uls.h"

void mx_print_folder_name(char *name, int num) {
    if(num != 0)
        mx_printstr("\n");
    mx_printstr(name);
    mx_printstr(":\n");
}

void mx_print_in_one_column(t_current_dir *head, char **flags) {
    while(head) {
        mx_print_file_name(head, flags, false);
        mx_printchar('\n');
        head = head->next;
    }
}

static void color_output(t_current_dir *head) {
    if (S_ISDIR(head->cur_stat.st_mode)) {
        if (mx_strcmp(head->name, "Shared") == 0 
            || mx_strcmp(head->name, "Caches") == 0 
            || mx_strcmp(head->name, "tmp") == 0) {
            mx_printstr(GREEN);
            mx_printstr(head->name);
            mx_printstr(NORM);
        }
		else {
            mx_printstr(BLUE);
            mx_printstr(head->name);
            mx_printstr(NORM);
        }
    }
	else if (S_ISLNK(head->cur_stat.st_mode)) {
		mx_printstr(MAG);
        mx_printstr(head->name);
        mx_printstr(NORM);
    }
    else if (S_ISFIFO(head->cur_stat.st_mode)) {
        mx_printstr(YELLOW);
        mx_printstr(head->name);
        mx_printstr(NORM);
    }
	else if (S_ISSOCK(head->cur_stat.st_mode)) {
		mx_printstr(MAG);
        mx_printstr(head->name);
        mx_printstr(NORM);
    }
	else if (S_ISCHR(head->cur_stat.st_mode)) {
        mx_printstr(BL_YEL);
        mx_printstr(head->name);
        mx_printstr(NORM);
    }
	else if (S_ISBLK(head->cur_stat.st_mode)) {
		mx_printstr(BL_CYN);
        mx_printstr(head->name);
        mx_printstr(NORM);
    }
	else if (S_ISXUSR(head->cur_stat.st_mode)) {
        if (mx_strcmp(head->name, "ps") == 0) {
            mx_printstr(REDRED);
            mx_printstr(head->name);
            mx_printstr(NORM);
        }
        else {
            mx_printstr(RED);
            mx_printstr(head->name);
            mx_printstr(NORM);
        }
    }
	else
		mx_printstr(head->name);
}

void mx_print_file_name(t_current_dir *head, char **flags, bool f) {
    if(mx_if_flag_activated('G', flags) && isatty(1))
        color_output(head);
    else
        mx_printstr(head->name);
    if(f)
        mx_printchar('\n');
}
