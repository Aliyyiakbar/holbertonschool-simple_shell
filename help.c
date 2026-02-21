#include "bash.h"

/**
 * b_help - print help
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_help(char **av, int *st)
{
	const char *n[] = {"exit", "env", "setenv", "unsetenv",
		"cd", "alias", "history", NULL};
	const char *u[] = {"exit [status]\n", "env\n",
		"setenv VARIABLE VALUE\n", "unsetenv VARIABLE\n",
		"cd [DIRECTORY]\n", "alias [name[='value'] ...]\n",
		"history\n", NULL};
	int i;

	if (av[1] == NULL)
	{
		printf("Builtins: exit env setenv unsetenv cd alias help history\n");
		*st = 0;
		return (BUILTIN_HANDLED);
	}
	for (i = 0; n[i] != NULL; i++)
	{
		if (strcmp(av[1], n[i]) == 0)
		{
			printf("%s", u[i]);
			*st = 0;
			return (BUILTIN_HANDLED);
		}
	}
	printf("help [BUILTIN]\n");
	*st = 0;
	return (BUILTIN_HANDLED);
}
