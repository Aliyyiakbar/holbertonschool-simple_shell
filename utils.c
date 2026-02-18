#include "bash.h"

int is_blank(const char *s)
{
	int i;

	if (s == NULL)
	{
		return (1);
	}

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' &&
			s[i] != '\r')
		{
			return (0);
		}
	}

	return (1);
}

int contains_slash(const char *s)
{
	int i;

	if (s == NULL)
	{
		return (0);
	}

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '/')
		{
			return (1);
		}
	}

	return (0);
}

char *str_duplicate(const char *s)
{
	size_t len;
	char *dup;

	if (s == NULL)
	{
		return (NULL);
	}

	len = strlen(s);
	dup = malloc(len + 1);
	if (dup == NULL)
	{
		return (NULL);
	}

	strcpy(dup, s);
	return (dup);
}

int str_to_int(const char *s, int *out)
{
	long v;
	int i;

	if (s == NULL || s[0] == '\0')
	{
		return (0);
	}

	v = 0;
	i = 0;
	if (s[i] == '+')
	{
		i++;
	}

	for (; s[i] != '\0'; i++)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return (0);
		}
		v = (v * 10) + (s[i] - '0');
		if (v > INT_MAX)
		{
			return (0);
		}
	}

	*out = (int)v;
	return (1);
}

void print_error(const char *prog, int line, const char *cmd)
{
	fprintf(stderr, "%s: %d: %s: not found\n", prog, line, cmd);
}
