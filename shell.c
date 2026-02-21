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

static int run(char **av, char *pr, int ln, int *st)
{
	pid_t pid;
	int ws;
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
	else if (pid < 0)
	{
		perror(pr);
		*st = 1;
	}
	else
	{
		if (waitpid(pid, &ws, 0) == -1)
		{
			perror(pr);
			*st = 1;
		}
		else if (WIFEXITED(ws))
		{
			*st = WEXITSTATUS(ws);
		}
		else
		{
			*st = 1;
		}
	}

	free(p);
	return (0);
}

int sh(char **av0)
{
	char *buf, **av;
	size_t cap;
	ssize_t n;
	int st, ln, br;

	buf = NULL;
	cap = 0;
	st = 0;
	ln = 0;

	g_tty = isatty(STDIN_FILENO);
	signal(SIGINT, sig_h);

	while (1)
	{
		if (g_tty)
		{
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		}

		n = getline(&buf, &cap, stdin);
		if (n == -1)
		{
			if (g_tty)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}

		ln++;
		if (is_sp(buf))
		{
			continue;
		}

		av = spl(buf, NULL);
		if (av == NULL || av[0] == NULL)
		{
			frev(av);
			continue;
		}

		br = b_run(av, &st);
		if (br == BUILTIN_EXIT)
		{
			frev(av);
			break;
		}
		if (br == BUILTIN_HANDLED)
		{
			frev(av);
			continue;
		}

		run(av, av0[0], ln, &st);
		frev(av);
	}

	free(buf);
	return (st);
}
