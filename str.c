#include "bash.h"

/**
 * s_len - string length
 * @s: input string
 * Return: length
 */
size_t s_len(const char *s)
{
	size_t n;

	if (s == NULL)
	{
		return (0);
	}
	n = 0;
	while (s[n])
	{
		n++;
	}
	return (n);
}

/**
 * s_cpy - copy string
 * @d: dst
 * @s: src
 * Return: dst
 */
char *s_cpy(char *d, const char *s)
{
	size_t i;

	if (d == NULL || s == NULL)
	{
		return (d);
	}
	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

/**
 * s_cmp - compare strings
 * @a: string a
 * @b: string b
 * Return: diff
 */
int s_cmp(const char *a, const char *b)
{
	size_t i;

	if (a == NULL && b == NULL)
	{
		return (0);
	}
	if (a == NULL)
	{
		return (-1);
	}
	if (b == NULL)
	{
		return (1);
	}
	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
	{
		i++;
	}
	return ((unsigned char)a[i] - (unsigned char)b[i]);
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

	n = s_len(s);
	d = malloc(n + 1);
	if (d == NULL)
	{
		return (NULL);
	}

	s_cpy(d, s);
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
