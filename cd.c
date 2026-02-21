#include "bash.h"

/**
 * b_cd - change directory
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_cd(char **av, int *st)
{
	char *dst;
	char *old;
	char *nw;

	dst = av[1];
	if (dst == NULL)
	{
		dst = getenv("HOME");
	}
	if (dst && strcmp(dst, "-") == 0)
	{
		dst = getenv("OLDPWD");
		if (dst == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			*st = 1;
			return (BUILTIN_HANDLED);
		}
	}
	old = getcwd(NULL, 0);
	if (dst == NULL || chdir(dst) != 0)
	{
		perror("cd");
		free(old);
		*st = 1;
		return (BUILTIN_HANDLED);
	}
	nw = getcwd(NULL, 0);
	if (old)
	{
		env_set("OLDPWD", old);
		free(old);
	}
	if (nw)
	{
		env_set("PWD", nw);
		if (av[1] && strcmp(av[1], "-") == 0)
		{
			printf("%s\n", nw);
		}
		free(nw);
	}
	*st = 0;
	return (BUILTIN_HANDLED);
}
