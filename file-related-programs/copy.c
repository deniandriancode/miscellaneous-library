#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024
#define PROGNAME "copy"

int copy_file (int argc, char *argv[]);

int
main (int argc, char *argv[])
{
	
        // check if program called with file and destination argument
	if (argc == 1) {
		fprintf (stderr, "%s: missing operand\n", PROGNAME);
		return 1;
	} else if (argc == 2) {
		fprintf (stderr, "%s: file destination required\n", PROGNAME);
		return 1;
	} else if (argc == 3) { // copy one file
                copy_file (argc, argv);
        } else {
        }
	
	return 0;
}

int
copy_file (int argc, char *argv[])
{
	FILE *in;
	FILE *out;
	char *buf;

	buf = (char *) malloc (BUFSIZE * sizeof (char));

	char *in_name = *(argv + 1); // get filename to be copied
	char *out_name = *(argv + 2); // get destination
	if (strcmp (out_name, ".") == 0) { // check if file copied to the same directory without renaming
		fprintf (stderr, "%s: file already exists\n", in_name);
		return 1;
	}

	
	in = fopen (in_name, "rb");
	if (in == NULL) {
		fprintf (stderr, "%s: cannot read '%s'; No such file\n", PROGNAME, in_name);
		return 1;
	}
	out = fopen (out_name, "wb");
	while (fread (buf, 1, BUFSIZE, in))
		fwrite (buf, 1, BUFSIZE, out);

	fclose (in);
	fclose (out);
	free (buf);
}
