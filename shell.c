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
