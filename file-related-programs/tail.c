#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

void strrev (char *msg);
void read_file_tail (char *filename, int line);

int
main (int argc, char *argv[])
{
        char *prog = "tail";
        int line;
        
        if (argc == 1) {
                fprintf (stderr, "%s: missing argument file\n", prog);
                return 1;
        }

        if ((*(++argv))[0] == '-' && (*argv)[1] == 'n') {
                line = atoi (*(++argv));
                read_file_tail (*(++argv), line);
        } else {
                line = 5;
                read_file_tail (*argv, line);
        }

        return 0;
}

void
strrev (char *msg)
{
        int l, i, tmp;

        l = strlen (msg);
        for (i = 0; i < l/2; ++i) {
                tmp = *(msg+i);
                *(msg+i) = *(msg+(l-i-2)); // do not swap the '\n' escape character
                *(msg+(l-i-2)) = tmp;
        }
}

void
read_file_tail (char *filename, int line)
{
        int lim, i, c, ibuf;
        int status;
        char *buf;
        FILE *fp;

        i = ibuf = 0;
        fp = fopen(filename, "r");
        buf = (char *) malloc (BUFSIZE * sizeof (char));
        fseek (fp, -2, SEEK_END);
        while (i < line) {
                c = fgetc (fp);
                buf[ibuf++] = c;
                if (c == '\n')
                        ++i;
                status = fseek (fp, -2, SEEK_CUR);
                if (status == -1)
                        break;
        }
        strrev (buf);
        printf ("%s\n", buf);
}
