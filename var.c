#include "bash.h"

/**
 * i2s - int to string
 * @v: value
 * Return: string
 */
static char *i2s(int v)
{
	char b[32];

	sprintf(b, "%d", v);
	return (sdup(b));
}

/**
 * vget - get var value
 * @s: token
 * @st: status
 * Return: new string or NULL
 */
static char *vget(char *s, int st)
{
	char *e;

	if (s[0] != '$' || s[1] == '\0')
	{
		return (NULL);
	}
	if (s[1] == '?')
	{
		return (i2s(st));
	}
	if (s[1] == '$')
	{
		return (i2s((int)getpid()));
	}
	e = env_get(s + 1);
	if (e == NULL)
	{
		return (sdup(""));
	}
	return (sdup(e));
}

/**
 * vrep - replace vars
 * @av: argv array
 * @st: status
 * Return: void
 */
void vrep(char **av, int st)
{
	int i;
	char *r;

	if (av == NULL)
	{
		return;
	}
	for (i = 0; av[i] != NULL; i++)
	{
		r = vget(av[i], st);
		if (r)
		{
			free(av[i]);
			av[i] = r;
		}
	}
}
