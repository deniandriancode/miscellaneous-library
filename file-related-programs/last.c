#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1028

int
main (int argc, char *argv[])
{
        FILE *fp;
        int pos;
        int c;

        fp = fopen ("ttx.txt", "r");
        fseek (fp, 0, SEEK_END);
        pos = ftell (fp);
        printf ("%d\n", pos);
        while ((c = getc (fp)) != EOF)
                putchar (c);

        fclose (fp);

        return 0;
}
