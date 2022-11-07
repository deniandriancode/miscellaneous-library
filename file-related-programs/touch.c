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

        index = 1;
        while (--argc >= 0) {
                char *filename = *(argv + index);
                if (filename) {
                        fp = fopen (filename, "w");
                        fclose (fp);
                        ++index;
                }
        }

        return 0;
}
