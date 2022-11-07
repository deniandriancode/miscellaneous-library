#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void remove_file (char *prog, char *filename);

int
main (int argc, char *argv[])
{
        char *prog = "remove";
        int i;

        if (argc == 1) {
                fprintf (stderr, "%s: missing operand\n", prog);
                return 1;
        }
        
        i = 1;
        while (--argc > 0) {
                char *filename = *(argv + i);
                if (filename) {
                        remove_file (prog, filename);
                        ++i;
                }
        }

        return 0;
}

void
remove_file (char *prog, char *filename)
{
        FILE *fp;

        fp = fopen (filename, "r");
        if (fp != NULL) {
                unlink (filename);
                fclose (fp);
        } else {
                fprintf (stderr, "%s: cannot remove '%s': No such file\n", prog, filename);
                exit (1);
        }
}
