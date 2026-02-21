#include "bash.h"

static int g_own;

/**
 * env_idx - find env index
 * @n: name
 * Return: index or -1
 */
static int env_idx(char *n)
{
	size_t ln;
	int i;

	if (environ == NULL)
	{
		return (-1);
	}
	ln = strlen(n);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], n, ln) == 0 && environ[i][ln] == '=')
		{
			return (i);
		}
	}
	return (-1);
}

/**
 * env_set - set env var
 * @n: name
 * @v: value
 * Return: 1 on ok
 */
int env_set(char *n, char *v)
{
	char *s;
	char **nv;
	int i;
	int cnt;

	if (n == NULL || v == NULL || n[0] == '\0' || strchr(n, '='))
	{
		return (0);
	}
	s = malloc(strlen(n) + strlen(v) + 2);
	if (s == NULL)
	{
		return (0);
	}
	sprintf(s, "%s=%s", n, v);
	i = env_idx(n);
	if (i >= 0)
	{
		environ[i] = s;
		return (1);
	}
	for (cnt = 0; environ && environ[cnt]; cnt++)
	{
	}
	nv = malloc(sizeof(char *) * (cnt + 2));
	if (nv == NULL)
	{
		free(s);
		return (0);
	}
	for (i = 0; i < cnt; i++)
	{
		nv[i] = environ[i];
	}
	nv[cnt] = s;
	nv[cnt + 1] = NULL;
	if (g_own)
	{
		free(environ);
	}
	environ = nv;
	g_own = 1;
	return (1);
}

/**
 * env_unset - unset env var
 * @n: name
 * Return: 1 on ok
 */
int env_unset(char *n)
{
	char **nv;
	int i;
	int j;
	int cnt;
	int idx;

	if (n == NULL || n[0] == '\0' || strchr(n, '='))
	{
		return (0);
	}
	idx = env_idx(n);
	if (idx < 0)
	{
		return (1);
	}
	for (cnt = 0; environ && environ[cnt]; cnt++)
	{
	}
	nv = malloc(sizeof(char *) * cnt);
	if (nv == NULL)
	{
		return (0);
	}
	for (i = 0, j = 0; i < cnt; i++)
	{
		if (i != idx)
		{
			nv[j++] = environ[i];
		}
	}
	nv[j] = NULL;
	if (g_own)
	{
		free(environ);
	}
	environ = nv;
	g_own = 1;
	return (1);
}
