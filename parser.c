#include "bash.h"

static int count_tokens(char *s)
{
	int n;
	char *tok;

	n = 0;
	tok = strtok(s, " \t\r\n");
	while (tok)
	{
		n++;
		tok = strtok(NULL, " \t\r\n");
	}

	return (n);
}

char **split_line(char *line, int *argc)
{
	char *copy;
	char *tok;
	char **av;
	int n;
	int i;

	if (line == NULL)
	{
		return (NULL);
	}

	copy = str_duplicate(line);
	if (copy == NULL)
	{
		return (NULL);
	}

	n = count_tokens(copy);
	free(copy);

	av = malloc(sizeof(char *) * (n + 1));
	if (av == NULL)
	{
		return (NULL);
	}

	i = 0;
	tok = strtok(line, " \t\r\n");
	while (tok)
	{
		av[i] = tok;
		i++;
		tok = strtok(NULL, " \t\r\n");
	}
	av[i] = NULL;

	if (argc)
	{
		*argc = n;
	}

	return (av);
}

void free_args(char **av)
{
	if (av)
	{
		free(av);
	}
}
