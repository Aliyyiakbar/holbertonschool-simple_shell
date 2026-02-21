#include "bash.h"

/**
 * b_env - print environment
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_env(char **av, int *st)
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

/**
 * b_set - handle setenv
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_set(char **av, int *st)
{
	if (av[1] == NULL || av[2] == NULL || av[3] != NULL)
	{
		fprintf(stderr, "setenv: usage: setenv VARIABLE VALUE\n");
		*st = 2;
		return (BUILTIN_HANDLED);
	}
	if (!env_set(av[1], av[2]))
	{
		fprintf(stderr, "setenv: failed\n");
		*st = 1;
		return (BUILTIN_HANDLED);
	}
	*st = 0;
	return (BUILTIN_HANDLED);
}

/**
 * b_unset - handle unsetenv
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_unset(char **av, int *st)
{
	if (av[1] == NULL || av[2] != NULL)
	{
		fprintf(stderr, "unsetenv: usage: unsetenv VARIABLE\n");
		*st = 2;
		return (BUILTIN_HANDLED);
	}
	if (!env_unset(av[1]))
	{
		fprintf(stderr, "unsetenv: failed\n");
		*st = 1;
		return (BUILTIN_HANDLED);
	}
	*st = 0;
	return (BUILTIN_HANDLED);
}
