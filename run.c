#include "bash.h"

/**
 * ch_run - exec child process
 * @av: argv array
 * @pr: program name
 * @ln: line number
 * @p: resolved path
 * Return: void
 */
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

/**
 * wpid - wait for child
 * @pid: child pid
 * @pr: program name
 * @st: status pointer
 * Return: 0
 */
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

/**
 * run - run external command
 * @av: argv array
 * @pr: program name
 * @ln: line number
 * @st: status pointer
 * Return: 0
 */
int run(char **av, char *pr, int ln, int *st)
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
