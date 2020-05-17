int mx_sqrt(int x) {
    int res = 0;

    if (x > 0) {
        for (int i = 1; i <= x/2; i++) {
            if (i * i == x)
                res = i;
        }
    }
    return res;
}
