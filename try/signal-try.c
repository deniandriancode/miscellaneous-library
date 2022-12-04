#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler (int signum);

int
main ()
{
	int i;
	signal (SIGINT, sig_handler);
	for (i = 0; i < 10; ++i) {
		printf ("@ECHO\n");
		sleep (1);
	}

	return 0;
}

void
sig_handler (int signum)
{
	printf ("\n\tinside handler fsunction\n");
}
