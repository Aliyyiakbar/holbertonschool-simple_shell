#include "bash.h"

static char **h_v;
static int h_n;
static int h_cap;
static int h_base;

/**
 * h_add - add to history
 * @s: line
 * Return: void
 */
void h_add(char *s)
{
	size_t n;
	char *c;
	char **nv;
	int nc;
	int i;

	if (s == NULL)
	{
		return;
	}
	n = s_len(s);
	if (n && s[n - 1] == '\n')
	{
		n--;
	}
	c = sdup_n(s, n);
	if (c == NULL)
	{
		return;
	}
	if (h_n + 1 > h_cap)
	{
		nc = (h_cap == 0) ? 16 : (h_cap * 2);
		nv = malloc(sizeof(char *) * nc);
		if (nv == NULL)
		{
			free(c);
			return;
		}
		for (i = 0; i < h_n; i++)
		{
			nv[i] = h_v[i];
		}
		free(h_v);
		h_v = nv;
		h_cap = nc;
	}
	h_v[h_n++] = c;
}

/**
 * b_hist - print history
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_hist(char **av, int *st)
{
	int i;

	(void)av;
	for (i = 0; i < h_n; i++)
	{
		printf("%d %s\n", (h_base + i) % 4096, h_v[i]);
	}
	*st = 0;
	return (BUILTIN_HANDLED);
}

/**
 * h_load - load history
 * Return: void
 */
void h_load(void)
{
	char *home;
	char *p;
	int fd;
	size_t n;
	char *ln;

	home = env_get("HOME");
	if (home == NULL)
	{
		return;
	}
	n = s_len(home) + s_len("/.simple_shell_history") + 1;
	p = malloc(n);
	if (p == NULL)
	{
		return;
	}
	sprintf(p, "%s/.simple_shell_history", home);
	fd = open(p, O_RDONLY);
	if (fd < 0)
	{
		free(p);
		return;
	}
	while ((ln = gl(fd)) != NULL)
	{
		h_add(ln);
		free(ln);
	}
	close(fd);
	free(p);
	h_base = h_n % 4096;
}

/**
 * h_save - save history
 * Return: void
 */
void h_save(void)
{
	char *home;
	char *p;
	int fd;
	int i;
	size_t n;

	home = env_get("HOME");
	if (home == NULL)
	{
		return;
	}
	n = s_len(home) + s_len("/.simple_shell_history") + 1;
	p = malloc(n);
	if (p == NULL)
	{
		return;
	}
	sprintf(p, "%s/.simple_shell_history", home);
	fd = open(p, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(p);
		return;
	}
	for (i = 0; i < h_n; i++)
	{
		write(fd, h_v[i], s_len(h_v[i]));
		write(fd, "\n", 1);
	}
	close(fd);
	free(p);
}

/**
 * h_free - free history
 * Return: void
 */
void h_free(void)
{
	int i;

	for (i = 0; i < h_n; i++)
	{
		free(h_v[i]);
	}
	free(h_v);
	h_v = NULL;
	h_n = 0;
	h_cap = 0;
}
