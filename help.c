#include "bash.h"

/**
 * b_help - print help
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_help(char **av, int *st)
{
	if (av[1] == NULL)
	{
		printf("Builtins: exit env setenv unsetenv cd alias help history\n");
		*st = 0;
		return (BUILTIN_HANDLED);
	}
	if (strcmp(av[1], "exit") == 0)
	{
		printf("exit [status]\n");
	}
	else if (strcmp(av[1], "env") == 0)
	{
		printf("env\n");
	}
	else if (strcmp(av[1], "setenv") == 0)
	{
		printf("setenv VARIABLE VALUE\n");
	}
	else if (strcmp(av[1], "unsetenv") == 0)
	{
		printf("unsetenv VARIABLE\n");
	}
	else if (strcmp(av[1], "cd") == 0)
	{
		printf("cd [DIRECTORY]\n");
	}
	else if (strcmp(av[1], "alias") == 0)
	{
		printf("alias [name[='value'] ...]\n");
	}
	else if (strcmp(av[1], "history") == 0)
	{
		printf("history\n");
	}
	else
	{
		printf("help [BUILTIN]\n");
	}
	*st = 0;
	return (BUILTIN_HANDLED);
}
