#include "uls.h"

static int get_flag_indx(char c, char **flags) {
    for (int i = 0; i < 10; i++) {
        if (c == flags[i][0])
            return i;
    }
    return -1;
}

static bool check_flag(char *str, char **flags) {
    int indx = -1;

    for(int i = 1; i < mx_strlen(str); i++) {
        indx = get_flag_indx(str[i], flags);
        if(indx == -1) {
            mx_invalid_flag(str[i]);
            mx_usage();
            return false;
        }
        else
            flags[indx][1] = '+';
    }
    return true;
}

int mx_parse_flags(int *i, char **flags, int argc, char *argv[]) {
    int num_of_files = argc - 1;

    for(int j = 1; j < argc; j++) {
        if(argv[j][0] == '-' && mx_strcmp(argv[j], "--") != 0) {
            if(check_flag(argv[j], flags)) {
                num_of_files--;
                (*i)++;
                continue;
            }
            else {
                mx_del_flags(flags);
                exit(1);
            }
            num_of_files--;
            (*i)++;
        }
        else if(mx_strcmp(argv[j], "--") == 0) {
            num_of_files--;
            (*i)++;
            break;
        }
        else
            break;
    }
    return num_of_files;
}

//видаляє масив флагів
void mx_del_flags(char **flags) {
    for(int i = 0; i < 10; i++)
        free(flags[i]);
    free(flags);
}

static void add_flags(char **flags) {
    flags[0][0] = 'R';
    flags[1][0] = 'a';
    flags[2][0] = 'l';
    flags[3][0] = '1';
    flags[4][0] = 'G';
    flags[5][0] = 'S';
    flags[6][0] = 't';
    flags[7][0] = 'A';
    flags[8][0] = 'u';
    flags[9][0] = 'T';
    // flags[10][0] = 'c';
    // flags[11][0] = 't';
    // flags[12][0] = 'C';
    // flags[13][0] = 'u';
    // flags[14][0] = 'S';
    // flags[15][0] = 'r';
}

//заповнює масив флагів
char **mx_fill_flag_arr() {
    char **flags = (char **)malloc(10 * sizeof(char *));

    for (int i = 0; i < 10; i++) {
        flags[i] = (char *)malloc(2 * sizeof(char));
        flags[i][1] = '-';
    }
    add_flags(flags);
    return flags;
}

//перевіряє чи флаг активований
bool mx_if_flag_activated(char f, char **flags) {
    for(int i = 0; i < 10; i++) {
        if(f == flags[i][0] && flags[i][1] == '+')
            return true;
    }
    return false;
}
