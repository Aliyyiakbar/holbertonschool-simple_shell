#include "bash.h"

static int g_tty;

int is_tty(void)
{
	return (g_tty);
}

void sig_h(int s)
{
	(void)s;

	if (g_tty)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	}
}

static void ch_run(char **av, char *pr, int ln, char *p)
{
	execve(p, av, environ);
	if (errno == EACCES)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
			pr, ln, av[0]);
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			pr, ln, av[0]);
	}
	free(p);
	exit(126);
}

static int wpid(pid_t pid, char *pr, int *st)
{
	int ws;

	if (waitpid(pid, &ws, 0) == -1)
	{
		perror(pr);
		*st = 1;
		return (0);
	}
	if (WIFEXITED(ws))
	{
		*st = WEXITSTATUS(ws);
	}
	else
	{
		*st = 1;
	}

	return (0);
}

static int run(char **av, char *pr, int ln, int *st)
{
	pid_t pid;
	char *p;

	p = rpath(av[0]);
	if (p == NULL)
	{
		p_err(pr, ln, av[0]);
		*st = 127;
		return (0);
	}

	pid = fork();
	if (pid == 0)
	{
		ch_run(av, pr, ln, p);
	}
	else if (pid < 0)
	{
		perror(pr);
		*st = 1;
	}
	else
	{
		wpid(pid, pr, st);
	}

	free(p);
	return (0);
}

static ssize_t gnl(char **b, size_t *cap, int tty)
{
	ssize_t n;

	if (tty)
	{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	}

	n = getline(b, cap, stdin);
	if (n == -1 && tty)
	{
		write(STDOUT_FILENO, "\n", 1);
	}

	return (n);
}

static int do_ln(char *buf, char *pr, int ln, int *st)
{
	char **av;
	int br;

	if (is_sp(buf))
	{
		return (0);
	}

	av = spl(buf, NULL);
	if (av == NULL || av[0] == NULL)
	{
		frev(av);
		return (0);
	}

	br = b_run(av, st);
	if (br == BUILTIN_EXIT)
	{
		frev(av);
		return (1);
	}
	if (br == BUILTIN_HANDLED)
	{
		frev(av);
		return (0);
	}

	run(av, pr, ln, st);
	frev(av);
	return (0);
}

int sh(char **av0)
{
	char *buf;
	size_t cap;
	ssize_t n;
	int st;
	int ln;

	buf = NULL;
	cap = 0;
	st = 0;
	ln = 0;

	g_tty = isatty(STDIN_FILENO);
	signal(SIGINT, sig_h);

	while (1)
	{
		n = gnl(&buf, &cap, g_tty);
		if (n == -1)
		{
			break;
		}

		ln++;
		if (do_ln(buf, av0[0], ln, &st))
		{
			break;
		}
	}

	free(buf);
	return (st);
}
