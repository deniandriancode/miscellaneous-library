#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LSH_RL_BUFSIZE 1024

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

#define PROGNAME "lsh"

void lsh_loop (void);
char* lsh_read_line (void);
char** lsh_split_line (char *line);
int lsh_launch (char **args);
int lsh_execute (char **args);

/*
 * Funcition prototypes for builtin shell commands
 */
int lsh_cd (char **args);
int lsh_help (char **args);
int lsh_exit (char **args);

int lsh_num_builtins (void);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit
};

int
main (int argc, char *argv[])
{
    // load config file

    // run command loop
    lsh_loop ();

    // perform any clean up

    return EXIT_SUCCESS;
}

void
lsh_loop (void)
{
    char *line;
    char **args;
    int status;

    do {
        line = lsh_read_line ();
        args = lsh_split_line (line);
        status = lsh_execute (args);

        free (line);
        free (args);
    } while (status);
}

// lsh_read_line: traditional implementation
// char*
// lsh_read_line (void)
/* {
//     int bufsize = LSH_RL_BUFSIZE;
//     int position = 0;
//     char *buffer = (char *) malloc (sizeof (char) * bufsize);
//     int c;
//
//     if (!buffer) {
//         fprintf (stderr, "%s: allocation error\n", PROGNAME);
//         exit (EXIT_FAILURE);
//     }
//
//     while (1) {
//         c = getchar ();
//
//         if (c == EOF || c == '\n') {
//             buffer[position] = '\0';
//             return buffer;
//         } else {
//             buffer[position] = c;
//         }
//         ++position;
//
//         if (position >= bufsize) {
//             bufsize += LSH_RL_BUFSIZE;
//             buffer = realloc (buffer, bufsize);
//
//             if (!buffer) {
//                 fprintf (stderr, "%s: allocation error\n", PROGNAME);
//                 exit (EXIT_FAILURE);
//             }
//         }
//     }
 }*/

// lsh_read_line: modern implementation
char*
lsh_read_line (void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us

    printf ("> "); // prompt the user
    if (getline (&line, &bufsize, stdin) == -1) {
        if (feof (stdin)) {
            exit (EXIT_SUCCESS);
        } else {
            perror ("readline");
            exit (EXIT_FAILURE);
        }
    }

    return line;
}

// lsh_split_line: split line to array of tokens
char**
lsh_split_line (char *line)
{
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = (char **) malloc (bufsize * sizeof (char *));
    char *token;

    if (!tokens) {
        fprintf (stderr, "%s: allocation error\n", PROGNAME);
        exit (EXIT_FAILURE);
    }

    token = strtok (line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        ++position;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc (tokens, bufsize * sizeof (char *));
            if (!tokens) {
                fprintf (stderr, "%s: allocation error\n", PROGNAME);
                exit (EXIT_FAILURE);
            }
        }

        token = strtok (NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int
lsh_launch (char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork ();
    if (pid == 0) {
        // child process
        if (execvp (args[0], args)) { // if it returns anything, an error has occurred
            perror (PROGNAME);
        }
        exit (EXIT_FAILURE);
    } else if (pid < 0) {
        // error forking
        perror (PROGNAME);
    } else {
        // parent process
        do {
            wpid = waitpid (pid, &status, WUNTRACED);
        } while (!WIFEXITED (status) && !WIFSIGNALED (status));
    }

    return 1;
}

int
lsh_execute (char **args)
{
    int i;

    if (args[0] == NULL) {
        // an empty command was entered
        return 1;
    }

    for (i = 0; i < lsh_num_builtins (); ++i) {
        if (strcmp (args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i]) (args);
        }
    }

    return lsh_launch (args);
}

/*
 * Function definition for shell builtin commands
 */

int
lsh_num_builtins (void)
{
    return sizeof (builtin_str) / sizeof (char *);
}

int lsh_cd (char **args)
{
    if (args[1] == NULL) {
        fprintf (stderr, "%s: expected argument to \"cd\"\n");
    } else {
        if (chdir (args[1]) != 0) {
            perror (PROGNAME);
        }
    }

    return 1;
}

int
lsh_help (char **args)
{
    int i;
    printf("Stephen Brennan's LSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < lsh_num_builtins (); ++i) {
        printf ("   %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int
lsh_exit (char **args)
{
    return 0;
}
