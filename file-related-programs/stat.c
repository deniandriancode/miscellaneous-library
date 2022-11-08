#include <stdio.h>
#include <sys/stat.h>

/* not finished yet 
 * How to print file permission in C */

int
main (int argc, char *argv[])
{
        struct stat buf;
        
        stat ("example.txt", &buf);

        printf ("%d\n", buf.st_mode);

        return 0;
}
