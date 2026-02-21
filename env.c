#include "bash.h"

static int g_own;

/**
 * env_dup - duplicate environ
 * @cnt: count output
 * Return: new environ or NULL
 */
static char **env_dup(int *cnt)
{
	char **nv;
	int i, n;

	for (n = 0; environ && environ[n]; n++)
	{
	}
	nv = malloc(sizeof(char *) * (n + 1));
	if (nv == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < n; i++)
	{
		nv[i] = sdup(environ[i]);
		if (nv[i] == NULL)
		{
			while (i-- > 0)
			{
				free(nv[i]);
			}
			free(nv);
			return (NULL);
		}
	}
	nv[n] = NULL;
	if (cnt)
	{
		*cnt = n;
	}
	return (nv);
}

/**
 * env_own - ensure owned environ
 * Return: 1 on ok
 */
static int env_own(void)
{
	char **nv;

	if (g_own)
	{
		return (1);
	}
	nv = env_dup(NULL);
	if (nv == NULL)
	{
		return (0);
	}
	environ = nv;
	g_own = 1;
	return (1);
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
	int i, cnt;
	if (n == NULL || v == NULL || n[0] == '\0' ||
		s_chr(n, '=') || !env_own())
	{
		return (0);
	}
	s = malloc(s_len(n) + s_len(v) + 2);
	if (s == NULL)
	{
		return (0);
	}
	sprintf(s, "%s=%s", n, v);
	i = env_idx(n);
	if (i >= 0)
	{
		free(environ[i]);
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
	free(environ);
	environ = nv;
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

	if (n == NULL || n[0] == '\0' || s_chr(n, '='))
	{
		return (0);
	}
	if (!env_own())
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
	free(environ[idx]);
	for (i = 0, j = 0; i < cnt; i++)
	{
		if (i != idx)
		{
			nv[j++] = environ[i];
		}
	}
	nv[j] = NULL;
	free(environ);
	environ = nv;
	return (1);
}

/**
 * env_free - free environ
 * Return: void
 */
void env_free(void)
{
	int i;

	if (!g_own)
	{
		return;
	}
	for (i = 0; environ && environ[i]; i++)
	{
		free(environ[i]);
	}
	free(environ);
	environ = NULL;
	g_own = 0;
}
