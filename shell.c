#include "bash.h"

static int g_tty;

/**
 * is_tty - get tty flag
 * Return: 1 if tty
 */
int is_tty(void)
{
	return (g_tty);
}

/**
 * sig_h - handle SIGINT
 * @s: signal number
 * Return: void
 */
void sig_h(int s)
{
	(void)s;

	if (g_tty)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	}
}

/**
 * do_ln - handle one line
 * @buf: input buffer
 * @pr: program name
 * @ln: line number
 * @st: status pointer
 * Return: 1 to break, 0 to continue
 */
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

/**
 * sh - main shell loop
 * @av0: argv
 * Return: status
 */
int sh(char **av0, int fd)
{
	char *buf;
	int st;
	int ln;

	st = 0;
	ln = 0;

	g_tty = isatty(fd);
	signal(SIGINT, sig_h);

	while (1)
	{
		if (g_tty)
		{
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		}

		buf = gl(fd);
		if (buf == NULL)
		{
			if (g_tty)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}

		ln++;
		if (do_ln(buf, av0[0], ln, &st))
		{
			free(buf);
			break;
		}
		free(buf);
	}

	return (st);
}
