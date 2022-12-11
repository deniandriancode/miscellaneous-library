#include <stdio.h>

int
main (int argc, char **argv)
{
        int i;

        while (1) {
                for (i = 1; *(argv + i); ++i) {
                        printf ("%s ", *(argv + i));
                }
                printf ("\b\n");
        }
}
