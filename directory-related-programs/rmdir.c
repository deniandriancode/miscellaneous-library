#include <stdio.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
	char *prog = "rmdir";
	int res;
	int i;
	
	if (argc == 1) {
		fprintf (stderr, "%s: missing operand\n", prog);
		return 1;
	}

	for (i = 1; --argc >= 0 && *(argv + i); ++i) {
		res = rmdir (*(argv + i));
		if (res) {
			fprintf (stderr, "%s: cannot remove '%s'; No such directory\n", prog, *(argv + 1));
			return 1;
		}
	}
	
	return 0;
}
