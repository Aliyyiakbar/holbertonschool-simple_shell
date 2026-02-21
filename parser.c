#include "bash.h"

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

void frev(char **av)
{
	if (av)
	{
		free(av);
	}
}
