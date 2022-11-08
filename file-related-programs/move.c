#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 1024

int
main (int argc, char *argv[])
{
	FILE *in;
	FILE *out;
	char *prog = "move";
	char *buf;
	
	if (argc == 1) {
		fprintf (stderr, "%s: missing operand\n", prog);
		return 1;
	} else if (argc == 2) {
		fprintf (stderr, "%s: file destination required\n", prog);
		return 1;
	}

	buf = (char *) malloc (BUFSIZE * sizeof (char));

	char *in_name = *(argv + 1);
	char *out_name = *(argv + 2);
	if (strcmp (out_name, ".") == 0) {
		fprintf (stderr, "%s: file already exists\n", in_name);
		return 1;
	}
	
	in = fopen (in_name, "rb");
	if (in == NULL) {
		fprintf (stderr, "%s: cannot read '%s'; No such file\n", prog, in_name);
		return 1;
	}

	out = fopen (out_name, "wb");
	while (fread (buf, 1, BUFSIZE, in))
		fwrite (buf, 1, BUFSIZE, out);

	fclose (in);
	fclose (out);
	free (buf);
	unlink (in_name);
	
	return 0;
}
