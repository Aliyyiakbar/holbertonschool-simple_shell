#include "bash.h"

/**
 * ctok - count tokens in string
 * @s: input string
 * Return: token count
 */
static int ctok(char *s)
{
	int n;
	char *t;

	n = 0;
	t = strtok(s, " \t\r\n");
	while (t)
	{
		n++;
		t = strtok(NULL, " \t\r\n");
	}

	return (n);
}

/**
 * fillv - fill argv array
 * @v: argv array
 * @s: input string
 * Return: void
 */
static void fillv(char **v, char *s)
{
	int i;
	char *t;

	i = 0;
	t = strtok(s, " \t\r\n");
	while (t)
	{
		v[i] = t;
		i++;
		t = strtok(NULL, " \t\r\n");
	}
	v[i] = NULL;
}

/**
 * spl - split line into tokens
 * @s: input string
 * @ac: argc output
 * Return: argv array
 */
char **spl(char *s, int *ac)
{
	char *c;
	char **v;
	int n;

	if (s == NULL)
	{
		return (NULL);
	}

	c = sdup(s);
	if (c == NULL)
	{
		return (NULL);
	}

	n = ctok(c);
	free(c);

	v = malloc(sizeof(char *) * (n + 1));
	if (v == NULL)
	{
		return (NULL);
	}

	fillv(v, s);

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
	if (av)
	{
		free(av);
	}
}
