#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int
main (int argc, char *argv[])
{
        FILE *fp;
        int c;
        char *buf;

        if (argc == 1) {
                while ((c = getchar ()) != EOF) {
                        putchar (c);
                }
        } else {
                buf = (char *) malloc (BUFSIZE * sizeof (char));
                fp = fopen (*(++argv), "r");
                while (fread (buf, 1, BUFSIZE, fp))
                        fwrite (buf, 1, BUFSIZE, stdout);

                fclose (fp);
                free (buf);
        }

        return 0;
}
