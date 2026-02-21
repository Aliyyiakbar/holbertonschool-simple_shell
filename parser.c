#include "bash.h"

/**
 * ws - check whitespace
 * @c: char
 * Return: 1 if whitespace
 */
static int ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

/**
 * op_len - operator length
 * @s: input string
 * @i: index
 * Return: op length or 0
 */
static int op_len(char *s, int i)
{
	if (s[i] == ';')
	{
		return (1);
	}
	if (s[i] == '&' && s[i + 1] == '&')
	{
		return (2);
	}
	if (s[i] == '|' && s[i + 1] == '|')
	{
		return (2);
	}
	return (0);
}

/**
 * push - push token
 * @v: vector
 * @n: count
 * @cap: cap
 * @s: token
 * Return: 1 on ok
 */
static int push(char ***v, int *n, int *cap, char *s)
{
	char **nv;
	int i;
	int nc;

	if (*n + 2 > *cap)
	{
		nc = (*cap == 0) ? 8 : (*cap * 2);
		nv = malloc(sizeof(char *) * nc);
		if (nv == NULL)
		{
			free(s);
			return (0);
		}
		for (i = 0; i < *n; i++)
		{
			nv[i] = (*v)[i];
		}
		free(*v);
		*v = nv;
		*cap = nc;
	}

	(*v)[*n] = s;
	(*n)++;
	(*v)[*n] = NULL;
	return (1);
}

/**
 * spl - split line into tokens
 * @s: input string
 * @ac: argc output
 * Return: argv array
 */
char **spl(char *s, int *ac)
{
	char **v;
	int n;
	int cap;
	int i;
	int st;
	int ln;
	char *t;

	if (s == NULL)
	{
		return (NULL);
	}

	v = NULL;
	n = 0;
	cap = 0;
	i = 0;
	while (s[i])
	{
		while (ws(s[i]))
		{
			i++;
		}
		if (s[i] == '\0')
		{
			break;
		}
		if (s[i] == '#' && (i == 0 || ws(s[i - 1])))
		{
			break;
		}
		ln = op_len(s, i);
		if (ln)
		{
			t = sdup_n(s + i, ln);
			if (t == NULL || !push(&v, &n, &cap, t))
			{
				frev(v);
				return (NULL);
			}
			i += ln;
			continue;
		}
		st = i;
		while (s[i] && !ws(s[i]) && !op_len(s, i))
		{
			i++;
		}
		t = sdup_n(s + st, i - st);
		if (t == NULL || !push(&v, &n, &cap, t))
		{
			frev(v);
			return (NULL);
		}
	}

	if (v == NULL)
	{
		v = malloc(sizeof(char *));
		if (v == NULL)
		{
			return (NULL);
		}
		v[0] = NULL;
	}

	if (ac)
	{
		*ac = n;
	}
	return (v);
}

/**
 * frev - free argv array
 * @av: argv array
 * Return: void
 */
void frev(char **av)
{
	int i;

	if (av == NULL)
	{
		return;
	}
	for (i = 0; av[i] != NULL; i++)
	{
		free(av[i]);
	}
	free(av);
}
