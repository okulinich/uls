#include "uls.h"

t_current_dir *mx_get_index_dir(int num, t_current_dir *head) {
    for(int i = 0; i < num; i++) {
        if(head)
            head = head->next;
        else
            return NULL;
    }
    return head;
}

void mx_set_spaces_zero(t_spaces *max) {
    max->link_spaces = 0;
    max->size_spaces = 0;
    max->owner_spaces = 0;
    max->group_spaces = 0;
    max->besides_owners = 0;
    max->major_spaces = 0;
    max->minor_spaces = 0;
    max->longest_name = 0;
    max->total = 0;
}

void mx_push_front_dir(char *name, t_current_dir **head, char *dir_name) {
    t_current_dir *new_item = (t_current_dir *)malloc(sizeof(t_current_dir));

    new_item->name = mx_strdup(name);
    new_item->dir_name = mx_strdup(dir_name);
    new_item->next = *head;
    *head = new_item;
}

void mx_fill_stat_info(char *name, t_current_dir *cur, char *dir_name, char **flags) {
    struct stat myCurrentStat;
    char *dir = mx_strjoin(dir_name, "/");
    char *rel_path = mx_strjoin(dir, name);
    char *temp = NULL;
    char *inode = NULL;

    lstat(rel_path, &myCurrentStat);
    cur->cur_stat = myCurrentStat;
    free(dir);
    free(rel_path);
}

void mx_del_list_dir(t_current_dir *head) {
    t_current_dir *temp = head;

    while(head) {
        free(head->dir_name);
        free(head->name);
        temp = head;
        head = head->next;
        free(temp);
    }
}

static void count_spaces_for_devices(t_current_dir *head, t_spaces *max_s, char **size) {
    if (S_ISBLK(head->cur_stat.st_mode) || S_ISCHR(head->cur_stat.st_mode)) {
        free(*size);
        *size = mx_itoa(minor(head->cur_stat.st_rdev));
        if(max_s->minor_spaces < mx_strlen(*size))
            max_s->minor_spaces = mx_strlen(*size);
        free(*size);
        *size = mx_itoa(major(head->cur_stat.st_rdev));
        if(max_s->major_spaces < mx_strlen(*size))
            max_s->major_spaces = mx_strlen(*size);
        free(*size);
        *size = NULL;
    }
}

void mx_count_total(t_current_dir *head, char **flags, t_spaces *max_s) {
    char *links = mx_itoa(head->cur_stat.st_nlink);
    char *size = mx_itoa(head->cur_stat.st_size);
    struct group *grp;
    char *group = NULL;
    char *owner = getpwuid(head->cur_stat.st_uid)->pw_name;

    grp = getgrgid(head->cur_stat.st_gid);
    if(grp)
        group = grp->gr_name;
    else
        group = mx_itoa(head->cur_stat.st_gid);
    max_s->total += head->cur_stat.st_blocks;
    if(max_s->link_spaces < mx_strlen(links))
        max_s->link_spaces = mx_strlen(links);
    if(max_s->size_spaces < mx_strlen(size))
        max_s->size_spaces = mx_strlen(size);
    if(max_s->group_spaces < mx_strlen(group))
        max_s->group_spaces = mx_strlen(group);
    if(max_s->owner_spaces < mx_strlen(owner))
        max_s->owner_spaces = mx_strlen(owner);
    if(max_s->besides_owners < mx_strlen(owner))
        max_s->besides_owners = mx_strlen(owner);
    count_spaces_for_devices(head, max_s, &size);
    free(links);
    if(size)
        free(size);
    if(!grp)
        free(group);
}

void mx_skip_hidden(t_current_dir **head) {
    t_current_dir *temp = *head;
    t_current_dir *del = NULL;
    int list_size = mx_find_list_size(*head);

    if (list_size > 1) {
        if ((*head)->name[0] == '.') {
            (*head) = (*head)->next;
            free(temp->name);
            free(temp->dir_name);
            free(temp);
            temp = *head;
        }
        while(temp->next) {
            if(temp->next->name[0] == '.') {
                del = temp->next;
                temp->next = temp->next->next;
                free(del->name);
                free(del->dir_name);
                free(del);
            }
            else
                temp = temp->next;
        }
    }
}

int mx_find_list_size(t_current_dir *head) {
    int size = 0;

    while(head) {
        size++;
        head = head->next;
    }
    return size;
}

