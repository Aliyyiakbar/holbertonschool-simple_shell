#ifndef BASH_H
#define BASH_H

#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern char **environ;

#define PROMPT "($) "
#define BUILTIN_NONE 0
#define BUILTIN_HANDLED 1
#define BUILTIN_EXIT 2

int shell_loop(char **av);
void sigint_handler(int sig);
int is_interactive(void);
char **split_line(char *line, int *argc);
void free_args(char **av);
int handle_builtin(char **av, int *st);
int builtin_exit(char **av, int *st);
int builtin_env(char **av, int *st);
char *resolve_path(char *cmd);
int is_blank(const char *s);
int contains_slash(const char *s);
char *str_duplicate(const char *s);
int str_to_int(const char *s, int *out);
void print_error(const char *pr, int ln, const char *cmd);

#endif
