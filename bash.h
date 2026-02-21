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

int sh(char **av);
void sig_h(int s);
int is_tty(void);
int run(char **av, char *pr, int ln, int *st);
char **spl(char *s, int *ac);
void frev(char **av);
int b_run(char **av, int *st);
int b_exit(char **av, int *st);
int b_env(char **av, int *st);
char *rpath(char *c);
int is_sp(const char *s);
int has_sl(const char *s);
char *sdup(const char *s);
int s2i(const char *s, int *o);
void p_err(const char *pr, int ln, const char *c);

#endif
