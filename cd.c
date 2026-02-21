#include "bash.h"

/**
 * cd_dst - get cd target
 * @av: argv array
 * @dst: target out
 * @st: status pointer
 * Return: 1 to continue, 0 to stop
 */
static int cd_dst(char **av, char **dst, int *st, char *pr, int ln)
{
	*dst = av[1];
	if (*dst == NULL)
	{
		*dst = env_get("HOME");
		if (*dst == NULL || (*dst)[0] == '\0')
		{
			*st = 0;
			return (0);
		}
	}
	if (s_cmp(*dst, "-") == 0)
	{
		*dst = env_get("OLDPWD");
		if (*dst == NULL)
		{
			fprintf(stderr, "%s: %d: cd: OLDPWD not set\n", pr, ln);
			*st = 1;
			return (0);
		}
	}
	return (1);
}

/**
 * b_cd - change directory
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_cd(char **av, int *st, char *pr, int ln)
{
	char *dst, *old, *nw;

	if (!cd_dst(av, &dst, st, pr, ln))
	{
		return (BUILTIN_HANDLED);
	}
	old = getcwd(NULL, 0);
	if (chdir(dst) != 0)
	{
		fprintf(stderr, "%s: %d: cd: can't cd to %s\n", pr, ln, dst);
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
		if (av[1] && s_cmp(av[1], "-") == 0)
		{
			printf("%s\n", nw);
		}
		free(nw);
	}
	*st = 0;
	return (BUILTIN_HANDLED);
}
