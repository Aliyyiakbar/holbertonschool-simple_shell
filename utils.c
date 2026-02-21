#include "bash.h"

/**
 * is_sp - check blank string
 * @s: input string
 * Return: 1 if blank, 0 else
 */
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

/**
 * has_sl - check slash in string
 * @s: input string
 * Return: 1 if slash, 0 else
 */
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

/**
 * sdup - duplicate string
 * @s: input string
 * Return: dup or NULL
 */
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

/**
 * s2i - convert string to int
 * @s: input string
 * @o: output int
 * Return: 1 on ok, 0 on fail
 */
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

/**
 * p_err - print error
 * @pr: program name
 * @ln: line number
 * @c: command
 * Return: void
 */
void p_err(const char *pr, int ln, const char *c)
{
	fprintf(stderr, "%s: %d: %s: not found\n", pr, ln, c);
}
