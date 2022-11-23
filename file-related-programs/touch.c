#include <stdio.h>

int
main (int argc, char *argv[])
{
        char *prog = "touch";
        FILE *fp;
        int index;

        if (argc == 1) {
                fprintf (stderr, "%s: require file argument\n", prog);
                return 1;
        }

        while (--argc > 0 && *(argv++)) {
                char *filename = *argv;

                if (fopen (filename, "r") != NULL) {
                        continue;
                }
                if (filename) {
                        fp = fopen (filename, "w");
                        fclose (fp);
                }
        }

        return 0;
}

