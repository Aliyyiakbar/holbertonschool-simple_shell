#include "bash.h"

static char **a_n;
static char **a_v;
static int a_sz;
static int a_cap;

/**
 * a_find - find alias index
 * @n: name
 * Return: index or -1
 */
static int a_find(char *n)
{
	int i;

	for (i = 0; i < a_sz; i++)
	{
		if (strcmp(a_n[i], n) == 0)
		{
			return (i);
		}
	}
	return (-1);
}

/**
 * a_get - get alias value
 * @n: name
 * Return: value or NULL
 */
char *a_get(char *n)
{
	int i;

	if ((i = a_find(n)) >= 0)
	{
		return (a_v[i]);
	}
	return (NULL);
}

/**
 * a_set - set alias
 * @n: name
 * @v: value
 * Return: 1 on ok
 */
static int a_set(char *n, char *v)
{
	int i;
	char **nn, **nv;
	i = a_find(n);
	if (i >= 0)
	{
		free(a_v[i]);
		a_v[i] = sdup(v);
		return (a_v[i] != NULL);
	}
	if (a_sz + 1 > a_cap)
	{
		a_cap = (a_cap == 0) ? 8 : (a_cap * 2);
		nn = malloc(sizeof(char *) * a_cap);
		nv = malloc(sizeof(char *) * a_cap);
		if (nn == NULL || nv == NULL)
		{
			free(nn);
			free(nv);
			return (0);
		}
		for (i = 0; i < a_sz; i++)
		{
			nn[i] = a_n[i];
			nv[i] = a_v[i];
		}
		free(a_n);
		free(a_v);
		a_n = nn;
		a_v = nv;
	}
	if ((a_n[a_sz] = sdup(n)) == NULL || (a_v[a_sz] = sdup(v)) == NULL)
	{
		free(a_n[a_sz]);
		free(a_v[a_sz]);
		return (0);
	}
	a_sz++;
	return (1);
}

/**
 * a_all - print all aliases
 * Return: void
 */
static void a_all(void)
{
	int i;

	for (i = 0; i < a_sz; i++)
	{
		printf("%s='%s'\n", a_n[i], a_v[i]);
	}
}

/**
 * b_alias - handle alias builtin
 * @av: argv array
 * @st: status pointer
 * Return: builtin code
 */
int b_alias(char **av, int *st)
{
	char *eq, *v;
	int i, j;
	*st = 0;
	if (av[1] == NULL)
	{
		a_all();
		return (BUILTIN_HANDLED);
	}
	for (i = 1; av[i] != NULL; i++)
	{
		eq = strchr(av[i], '=');
		if (eq == NULL)
		{
			j = a_find(av[i]);
			if (j >= 0)
			{
				printf("%s='%s'\n", a_n[j], a_v[j]);
			}
			continue;
		}
		*eq = '\0';
		v = eq + 1;
		if (v[0] == '\'')
		{
			j = (int)strlen(v);
			if (j > 1 && v[j - 1] == '\'')
			{
				v[j - 1] = '\0';
				v++;
			}
		}
		if (!a_set(av[i], v))
		{
			*st = 1;
		}
	}
	return (BUILTIN_HANDLED);
}
