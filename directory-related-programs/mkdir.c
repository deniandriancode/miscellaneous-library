#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int
main (int argc, char *argv[])
{
	char *prog = "mkdir";
	DIR *dir_name;
	mode_t dir_mode;
	int res;
	int i;
	
	if (argc == 1) {
		fprintf (stderr, "%s: missing operand\n", prog);
		return 1;
	}

	dir_mode = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	for (i = 1; --argc >= 0 && *(argv + i); ++i) {
		dir_name = opendir (*(argv + i));
		if (dir_name) {
			fprintf (stderr, "%s: directory '%s' exists; Cannot create directory\n", prog, *(argv + i));
			continue;
		}
		res = mkdir (*(argv + i), dir_mode);
		if (res != 0) // if error, then end the program
			break;
	}

	return 0;
}
