#include "bash.h"

int handle_builtin(char **av, int *st)
{
	if (av == NULL || av[0] == NULL)
	{
		return (BUILTIN_NONE);
	}

	if (strcmp(av[0], "exit") == 0)
	{
		return (builtin_exit(av, st));
	}

	if (strcmp(av[0], "env") == 0)
	{
		return (builtin_env(av, st));
	}

	return (BUILTIN_NONE);
}

int builtin_exit(char **av, int *st)
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
		if (str_to_int(av[1], &n) == 0)
		{
			fprintf(stderr, "exit: Illegal number: %s\n", av[1]);
			*st = 2;
			return (BUILTIN_HANDLED);
		}
		*st = n % 256;
	}

	return (BUILTIN_EXIT);
}

int builtin_env(char **av, int *st)
{
	int i;

	(void)av;

	if (environ == NULL)
	{
		*st = 0;
		return (BUILTIN_HANDLED);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	*st = 0;
	return (BUILTIN_HANDLED);
}
