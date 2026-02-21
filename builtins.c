#include "bash.h"

/**
 * b_run - run builtin if match
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_run(char **av, int *st)
{
	if (av == NULL || av[0] == NULL)
	{
		return (BUILTIN_NONE);
	}
	if (strcmp(av[0], "exit") == 0)
	{
		return (b_exit(av, st));
	}
	if (strcmp(av[0], "env") == 0)
	{
		return (b_env(av, st));
	}
	if (strcmp(av[0], "setenv") == 0)
	{
		return (b_set(av, st));
	}
	if (strcmp(av[0], "unsetenv") == 0)
	{
		return (b_unset(av, st));
	}
	if (strcmp(av[0], "cd") == 0)
	{
		return (b_cd(av, st));
	}
	if (strcmp(av[0], "alias") == 0)
	{
		return (b_alias(av, st));
	}
	if (strcmp(av[0], "help") == 0)
	{
		return (b_help(av, st));
	}
	if (strcmp(av[0], "history") == 0)
	{
		return (b_hist(av, st));
	}
	return (BUILTIN_NONE);
}

/**
 * b_exit - handle exit builtin
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_exit(char **av, int *st)
{
	int n;

	if (av[1] != NULL)
	{
		if (av[2] != NULL)
		{
			fprintf(stderr, "exit: too many arguments\n");
			*st = 2;
			return (BUILTIN_HANDLED);
		}
		if (s2i(av[1], &n) == 0)
		{
			fprintf(stderr, "exit: Illegal number: %s\n", av[1]);
			*st = 2;
			return (BUILTIN_HANDLED);
		}
		*st = n % 256;
	}

	return (BUILTIN_EXIT);
}
