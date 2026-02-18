#include "bash.h"

static int count_tokens(char *line)
{
	int count;
	char *token;

	count = 0;
	token = strtok(line, " \t\r\n");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t\r\n");
	}

	return (count);
}

char **split_line(char *line, int *argc)
{
	char *copy;
	char *token;
	char **args;
	int count;
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

	count = count_tokens(copy);
	free(copy);

	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
	{
		return (NULL);
	}

	i = 0;
	token = strtok(line, " \t\r\n");
	while (token)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;

	if (argc)
	{
		*argc = count;
	}

	return (args);
}

void free_args(char **args)
{
	if (args)
	{
		free(args);
	}
}
