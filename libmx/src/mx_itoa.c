#include "./libmx.h"

static void sign_and_size(int *sign, int *size, int *number, int *flag) {
    int copy_number = *number;

    if(*number == -2147483648) {
        *flag = 1;
        (*number) += 1;
    }
    if ((*number) < 0) {
        (*sign) = -1;
        (*size)++;
        (*number) *= -1;
        copy_number = *number;
    }
    while (copy_number > 0) {
        (*size)++;
        copy_number /= 10;
    }
}

char *mx_itoa(int number) {
    int size = 0;
    char *res = NULL;
    int sign = 1;
    int flag = 0;

    if (number == 0) {
        res = mx_strnew(1);
        res[0] = '0';
    }
    else {
        sign_and_size(&sign, &size, &number, &flag);
        res = mx_strnew(size);
        while(number > 0) {
            res[--size] = number % 10 + '0';
            number /= 10;
        }
        res[0] = (sign == -1) ? '-' : res[0];
        res[10] = (flag == 1) ? '8' : res[10];
    }
    return res;
}
