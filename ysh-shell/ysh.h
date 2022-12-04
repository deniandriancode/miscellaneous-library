#ifndef YSH_H
#define YSH_H
#define PROGNAME "ysh"

#define YSH_LINE_BUFSIZE 1024

#define YSH_TOK_BUFSIZE 64
#define YSH_TOK_DELIM " \t\n\a"

/*
 * Function prototypes of builtin shell commands
 *
 */
int ysh_builtin_cd (char **args);
int ysh_builtin_help (char **args);
int ysh_builtin_exit (char **args);
int builtin_nums (void);

extern char *builtin_str[];

extern int (*builtin_func[]) (char **args);

#endif
