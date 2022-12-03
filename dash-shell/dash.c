#include <stdio.h>
#include <stdlib.h>

#define DASH_LINE_BUFSIZE 1024

void dash_loop (void);
char* dash_read_line (void);
char** dash_parse_line (char *line);
int dash_execute (char **args);

int
main (int argc, char **argv)
{
    // load config file

    // call shell main loop
    dash_loop ();

    // clean up

    return EXIT_SUCCESS;
}

/*
 * dash_loop: main loop of shell
 */
void
dash_loop (void)
{
    char *line;
    char **args;
    int status;

    do {
        line = dash_read_line (); // read
        args = dash_parse_line (line); // parse
        status = dash_execute (args); // execute

        free (line);
        free (args);
    } while (status);
}

/*
 * dash_read_line: read line from stdin
 */
char*
dash_read_line (void)
{
    char *line;
    size_t bufsize;

    bufsize = 0;
}

/*
 * dash_parse_line: parse and tokenize line input
 */
char**
dash_parse_line (char *line)
{

}

/*
 * dash_execute: execute user command
 */
int
dash_execute (char **args)
{

}
