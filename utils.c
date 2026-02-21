#include "bash.h"

int is_sp(const char *s)
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

int has_sl(const char *s)
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

char *sdup(const char *s)
{
	size_t n;
	char *d;

	if (s == NULL)
	{
		return (NULL);
	}

	n = strlen(s);
	d = malloc(n + 1);
	if (d == NULL)
	{
		return (NULL);
	}

	strcpy(d, s);
	return (d);
}

int s2i(const char *s, int *o)
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

	*o = (int)v;
	return (1);
}

void p_err(const char *pr, int ln, const char *c)
{
	fprintf(stderr, "%s: %d: %s: not found\n", pr, ln, c);
}
