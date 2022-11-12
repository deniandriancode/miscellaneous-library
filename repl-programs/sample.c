#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 2048

/* not finished yet */
void parse_cmd (char *cmd);

int
main (int argc, char *argv[])
{
        char *buf;
        int c;

        buf = (char *) malloc (BUFSIZE * sizeof (char));
        while ((c = getchar ()) != EOF) {
                if (c != '\n') {
                        *buf = c;
                        ++buf;
                } else {
                        parse_cmd (buf);
                }
        }

        return 0;
}

void
parse_cmd (char *cmd)
{
        if (strcmp (cmd, "hello") == 0) {
                printf ("Well Hello there!\n");
        } else {
                printf ("%s", cmd);
                printf ("\n");
        }
}
