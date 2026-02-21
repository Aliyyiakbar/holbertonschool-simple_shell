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
 * sh - main shell loop
 * @av0: argv
 * @fd: input fd
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
		if (exec_ln(buf, av0[0], &st, ln))
		{
			free(buf);
			break;
		}
		free(buf);
	}

	return (st);
}
