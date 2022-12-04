#include <stdio.h>
#include <readline/readline.h>

int
main (int argc, char **argv)
{
	char *line;

	line = readline ("Enter your name: ");
	printf ("Hello %s!\n");

	return 0;
}
