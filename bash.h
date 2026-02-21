#ifndef BASH_H
#define BASH_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

extern char **environ;
extern char **a_n;
extern char **a_v;
extern int a_sz;
extern int a_cap;

#define PROMPT "($) "
#define BUILTIN_NONE 0
#define BUILTIN_HANDLED 1
#define BUILTIN_EXIT 2

int sh(char **av, int fd);
void sig_h(int s);
int is_tty(void);
int run(char **av, char *pr, int ln, int *st);
char *gl(int fd);
int exec_ln(char *buf, char *pr, int *st, int ln);
char **spl(char *s, int *ac);
void frev(char **av);
int b_run(char **av, int *st, char *pr, int ln);
int b_exit(char **av, int *st, char *pr, int ln);
int b_env(char **av, int *st);
int b_set(char **av, int *st);
int b_unset(char **av, int *st);
int b_cd(char **av, int *st, char *pr, int ln);
int b_alias(char **av, int *st);
int b_help(char **av, int *st);
int b_hist(char **av, int *st);
int env_set(char *n, char *v);
int env_unset(char *n);
int env_idx(char *n);
void env_free(void);
void vrep(char **av, int st);
char *a_get(char *n);
char **a_exp(char **av);
void a_free(void);
void h_add(char *s);
void h_load(void);
void h_save(void);
void h_free(void);
char *rpath(char *c);
int is_sp(const char *s);
int has_sl(const char *s);
size_t s_len(const char *s);
char *s_cpy(char *d, const char *s);
int s_cmp(const char *a, const char *b);
int s_ncmp(const char *a, const char *b, size_t n);
char *s_chr(const char *s, int c);
char *sdup(const char *s);
char *sdup_n(const char *s, size_t n);
int s2i(const char *s, int *o);
void p_err(const char *pr, int ln, const char *c);
char *env_get(const char *n);

#endif
