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
 * try_dir - try one dir
 * @d: dir
 * @c: cmd
 * @fd: found path
 * @pc: PATH copy
 * Return: path or NULL
 */
static char *try_dir(char *d, char *c, char **fd, char *pc)
{
	char *p;

	p = mk_path(d, c);
	if (p && access(p, X_OK) == 0)
	{
		if (*fd)
		{
			free(*fd);
		}
		free(pc);
		return (p);
	}
	if (p && access(p, F_OK) == 0 && *fd == NULL)
	{
		*fd = p;
		return (NULL);
	}
	free(p);
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
	char *d, *fd, *p;
	size_t i, st, ln;
	fd = NULL;
	i = 0;
	st = 0;
	while (1)
	{
		if (pc[i] == ':' || pc[i] == '\0')
		{
			ln = i - st;
			d = (ln == 0) ? sdup(".") : sdup_n(pc + st, ln);
			if (d == NULL)
			{
				free(fd);
				free(pc);
				return (NULL);
			}
			p = try_dir(d, c, &fd, pc);
			free(d);
			if (p)
			{
				return (p);
			}
			if (pc[i] == '\0')
			{
				break;
			}
			st = i + 1;
		}
		i++;
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
		if (access(c, X_OK) == 0 || access(c, F_OK) == 0)
		{
			return (sdup(c));
		}
		return (NULL);
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
