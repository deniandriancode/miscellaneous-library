/*
  watch directory for changes
  TODO: apply dynamic allocation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define DIRBUF 1024

void dir_loop ();
void dir_check_change (char **ls_prev, char **ls_curr);
void replace_arr (char **target, char **value);

int
main (int argc, char *argv[])
{
	DIR *init_dir;
	useconds_t mcs;

	mcs = 500000; /* sleep for 0.5 second */

	while (1) {
		dir_loop ();
		usleep (mcs);
	}
	
	return 0;
}

void
dir_loop ()
{
	DIR *dir;
	struct dirent *drn;
	static char **ls_dir_init;
	char **ls_dir_curr;
	int i;

	dir = opendir (".");
	i = 0;
	
	if (ls_dir_init == NULL) {
		/* initialize ls_dir_init */
		ls_dir_init = (char **) malloc (DIRBUF * sizeof (char *));
		while (drn = readdir (dir)) {
			*(ls_dir_init + i) = drn->d_name;
			++i;
		}
	} else {
		/* compare init and current ls */
		ls_dir_curr = (char **) malloc (DIRBUF * sizeof (char *));
		while (drn = readdir (dir)) {
			*(ls_dir_curr + i) = drn->d_name;
			++i;
		}

	    dir_check_change (ls_dir_init, ls_dir_curr);
	}
}

void
dir_check_change (char **ls_prev, char **ls_curr)
{
	int i;
	
	for (i = 0; *(ls_prev + i) && *(ls_curr + i); ++i) {
		if (strcmp (*(ls_prev + i), *(ls_curr + i)) != 0) {
			printf ("change detected!\n");
			replace_arr (ls_prev, ls_curr);
			break;
		}
	}
}

/*
  replace_arr: replace value of target with value
*/
void
replace_arr (char **target, char **value)
{
	int i;

	target = (char **) realloc (target, DIRBUF * sizeof (char *));

	for (i = 0; *(value + i); ++i) {
		*(target + i) = *(value + i);
	}
}
