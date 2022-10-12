#include<stdio.h>

int read() {
    int x = 0;
    int flag = 1;
    char a = getchar(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    while ('0' > a || '9' < a) {
        if (a == '-')
            flag = -1;
        a = getchar(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    }
    while ('0' <= a && a <= '9') {
        x = x * 10 + a - '0';
        a = getchar(); // NOLINT(cppcoreguidelines-narrowing-conversions)
    }
    return flag * x;
}

void write(int x) // NOLINT(misc-no-recursion)
{
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int main(void) {
    write(read()+read());
    return 0;
}
