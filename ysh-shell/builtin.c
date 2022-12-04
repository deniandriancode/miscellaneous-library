#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ysh.h"

char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **args) = {
	&ysh_builtin_cd,
	&ysh_builtin_help,
	&ysh_builtin_exit
};

/*
 * Function declaration of builtin shell commands
 *
 */
int
ysh_builtin_cd (char **args)
{
	if (chdir (args[1])) {
		perror (PROGNAME);
		exit (EXIT_FAILURE);
	}

	return 1;
}

int
ysh_builtin_help (char **args)
{
	printf ("Deni Andrian Prayoga: YShell, just shell\n");
	return 1;
}

int
ysh_builtin_exit (char **args)
{
	printf ("exit\n");
	return EXIT_SUCCESS;
}

/*
 * builtin_nums: get the length of builtin commands
 */
int
builtin_nums (void)
{
	return sizeof (builtin_str) / sizeof (char *);
}
