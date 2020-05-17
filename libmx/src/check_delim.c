int mx_check_delim(char *str, char delim) {
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == delim)
            return i;
    return -1;
}
