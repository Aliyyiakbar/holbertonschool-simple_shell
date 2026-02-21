#include "bash.h"

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

char *rpath(char *c)
{
	char *pe, *pc, *t, *p, *fd;

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
