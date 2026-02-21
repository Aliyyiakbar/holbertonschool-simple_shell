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

char **spl(char *s, int *ac)
{
	char *c;
	char *t;
	char **v;
	int n;
	int i;

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

	i = 0;
	t = strtok(s, " \t\r\n");
	while (t)
	{
		v[i] = t;
		i++;
		t = strtok(NULL, " \t\r\n");
	}
	v[i] = NULL;

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
