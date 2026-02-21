#include "bash.h"

/**
 * b_run - run builtin if match
 * @av: argv array
 * @st: status pointer
 * @pr: program name
 * @ln: line number
 * Return: builtin code
 */
int b_run(char **av, int *st, char *pr, int ln)
{
	if (av == NULL || av[0] == NULL)
	{
		return (BUILTIN_NONE);
	}
	if (s_cmp(av[0], "exit") == 0)
	{
		return (b_exit(av, st, pr, ln));
	}
	if (s_cmp(av[0], "env") == 0)
	{
		return (b_env(av, st));
	}
	if (s_cmp(av[0], "setenv") == 0)
	{
		return (b_set(av, st));
	}
	if (s_cmp(av[0], "unsetenv") == 0)
	{
		return (b_unset(av, st));
	}
	if (s_cmp(av[0], "cd") == 0)
	{
		return (b_cd(av, st, pr, ln));
	}
	if (s_cmp(av[0], "alias") == 0)
	{
		return (b_alias(av, st));
	}
	if (s_cmp(av[0], "help") == 0)
	{
		return (b_help(av, st));
	}
	if (s_cmp(av[0], "history") == 0)
	{
		return (b_hist(av, st));
	}
	return (BUILTIN_NONE);
}

/**
 * b_exit - handle exit builtin
 * @av: argv array
 * @st: status pointer
 * @pr: program name
 * @ln: line number
 * Return: builtin code
 */
int b_exit(char **av, int *st, char *pr, int ln)
{
	int n;

	if (av[1] != NULL)
	{
		if (av[2] != NULL)
		{
			fprintf(stderr, "%s: %d: exit: too many arguments\n", pr, ln);
			*st = 2;
			return (BUILTIN_HANDLED);
		}
		if (s2i(av[1], &n) == 0)
		{
			fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
				pr, ln, av[1]);
			*st = 2;
			return (BUILTIN_HANDLED);
		}
		*st = n % 256;
	}

	return (BUILTIN_EXIT);
}
