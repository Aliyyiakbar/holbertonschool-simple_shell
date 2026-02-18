#include "bash.h"

int handle_builtin(char **args, int *status)
{
	if (args == NULL || args[0] == NULL)
	{
		return (BUILTIN_NONE);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		return (builtin_exit(args, status));
	}

	if (strcmp(args[0], "env") == 0)
	{
		return (builtin_env(args, status));
	}

	return (BUILTIN_NONE);
}

int builtin_exit(char **args, int *status)
{
	int code;

	if (args[1] != NULL)
	{
		if (args[2] != NULL)
		{
			fprintf(stderr, "exit: too many arguments\n");
			*status = 2;
			return (BUILTIN_HANDLED);
		}
		if (str_to_int(args[1], &code) == 0)
		{
			fprintf(stderr, "exit: Illegal number: %s\n", args[1]);
			*status = 2;
			return (BUILTIN_HANDLED);
		}
		*status = code % 256;
	}

	return (BUILTIN_EXIT);
}

int builtin_env(char **args, int *status)
{
	int i;

	(void)args;

	if (environ == NULL)
	{
		*status = 0;
		return (BUILTIN_HANDLED);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	*status = 0;
	return (BUILTIN_HANDLED);
}
