#include "bash.h"

/**
 * env_path - get PATH env value
 * Return: PATH string or NULL
 */
static char *env_path(void)
{
	int i;
	size_t ln;

	ln = strlen("PATH=");
	if (environ == NULL)
	{
		return (NULL);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", ln) == 0)
		{
			return (environ[i] + ln);
		}
	}

	return (NULL);
}

/**
 * mk_path - join dir and cmd
 * @d: dir
 * @c: cmd
 * Return: full path or NULL
 */
static char *mk_path(const char *d, const char *c)
{
	size_t n;
	char *p;

	n = strlen(d) + strlen(c) + 2;
	p = malloc(n);
	if (p == NULL)
	{
		return (NULL);
	}

	sprintf(p, "%s/%s", d, c);
	return (p);
}

/**
 * sl_ok - check slash path
 * @c: cmd path
 * Return: dup path or NULL
 */
static char *sl_ok(char *c)
{
	if (access(c, X_OK) == 0 || access(c, F_OK) == 0)
	{
		return (sdup(c));
	}

	return (NULL);
}

/**
 * scan - scan PATH for cmd
 * @pc: PATH copy
 * @c: cmd
 * Return: found path or NULL
 */
static char *scan(char *pc, char *c)
{
	char *t;
	char *p;
	char *fd;

	fd = NULL;
	t = strtok(pc, ":");
	while (t)
	{
		p = mk_path(t, c);
		if (p && access(p, X_OK) == 0)
		{
			if (fd)
			{
				free(fd);
			}
			free(pc);
			return (p);
		}
		if (p && access(p, F_OK) == 0 && fd == NULL)
		{
			fd = p;
		}
		else
		{
			free(p);
		}
		t = strtok(NULL, ":");
	}

	free(pc);
	return (fd);
}

/**
 * rpath - resolve cmd path
 * @c: cmd
 * Return: resolved path or NULL
 */
char *rpath(char *c)
{
	char *pe;
	char *pc;

	if (c == NULL || c[0] == '\0')
	{
		return (NULL);
	}

	if (has_sl(c))
	{
		return (sl_ok(c));
	}

	pe = env_path();
	if (pe == NULL)
	{
		return (NULL);
	}

	pc = sdup(pe);
	if (pc == NULL)
	{
		return (NULL);
	}

	return (scan(pc, c));
}
