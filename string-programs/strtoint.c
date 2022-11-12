#include <stdio.h>
#include <string.h>

int strtoint (char *str);
int power (int base, int n);

int
main (int argc, char *argv[])
{
        int n;

        n = strtoint (*(++argv));
        printf ("%d\n", n);

        return 0;
}

int
strtoint (char *str)
{
        int base;
        int c, ord, length;
        int res;

        length = strlen (str);
        base = (int) '0';
        ord = power (10, length - 1); /* multiplier */
        res = 0;
        while ((c = *(str++)) != '\0') {
                res += (c - base) * ord;
                ord /= 10;
        }

        return res;
}

int
power (int base, int n)
{
        int res;

        if (base == 0)
                return 1;

        res = 1;
        while (n > 0) {
                res *= base;
                --n;
        }

        return res;
}
