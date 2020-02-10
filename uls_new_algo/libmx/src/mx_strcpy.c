char *mx_strcpy(char *dst, const char *src) {
    char *dst_copy = dst;

    for (int i = 0; (dst[i] = src[i]) != '\0'; i++)
        ;
    return dst_copy;
}
