#include <stdio.h>
#include <stdlib.h>

void read_file_head (char *filename, int line);

int
main (int argc, char *argv[])
{
        char *prog = "head";
        int line;
        
        if (argc == 1) {
                fprintf (stderr, "%s: missing argument file\n", prog);
                return 1;
        }

        if ((*(++argv))[0] == '-' && (*argv)[1] == 'n') {
                line = atoi (*(++argv));
                read_file_head (*(++argv), line);
        } else {
                line = 5;
                read_file_head (*argv, line);
        }

        return 0;
}

void
read_file_head (char *filename, int line)
{
        FILE *fp;
        int i, c;

        i = 0;
        fp = fopen (filename, "r");
        while ((c = fgetc (fp)) != EOF && i < line) {
                if (c == '\n')
                        ++i;
                putchar (c);
        }
        fclose (fp);
}
