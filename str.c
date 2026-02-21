#include "bash.h"

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
 * sdup_n - duplicate n chars
 * @s: input string
 * @n: count
 * Return: dup or NULL
 */
char *sdup_n(const char *s, size_t n)
{
	size_t i;
	char *d;

	if (s == NULL)
	{
		return (NULL);
	}

	d = malloc(n + 1);
	if (d == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < n; i++)
	{
		d[i] = s[i];
	}
	d[i] = '\0';
	return (d);
}
