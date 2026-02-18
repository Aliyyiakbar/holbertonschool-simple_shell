#include "bash.h"

static int g_int;

int is_interactive(void)
{
	return (g_int);
}

void sigint_handler(int sig)
{
	(void)sig;

	if (g_int)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	}
}

static int run_cmd(char **av, char *pr, int ln, int *st)
{
	pid_t pid;
	int ws;
	char *path;

	path = resolve_path(av[0]);
	if (path == NULL)
	{
		print_error(pr, ln, av[0]);
		*st = 127;
		return (0);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(path, av, environ);
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
		free(path);
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

	free(path);
	return (0);
}

int shell_loop(char **argv)
{
	char *buf;
	size_t cap;
	ssize_t n;
	char **av;
	int st;
	int ln;
	int br;

	buf = NULL;
	cap = 0;
	st = 0;
	ln = 0;

	g_int = isatty(STDIN_FILENO);
	signal(SIGINT, sigint_handler);

	while (1)
	{
		if (g_int)
		{
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		}

		n = getline(&buf, &cap, stdin);
		if (n == -1)
		{
			if (g_int)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}

		ln++;
		if (is_blank(buf))
		{
			continue;
		}

		av = split_line(buf, NULL);
		if (av == NULL || av[0] == NULL)
		{
			free_args(av);
			continue;
		}

		br = handle_builtin(av, &st);
		if (br == BUILTIN_EXIT)
		{
			free_args(av);
			break;
		}
		if (br == BUILTIN_HANDLED)
		{
			free_args(av);
			continue;
		}

		run_cmd(av, argv[0], ln, &st);
		free_args(av);
	}

	free(buf);
	return (st);
}
