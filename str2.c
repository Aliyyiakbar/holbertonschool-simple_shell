#include "bash.h"

/**
 * s_ncmp - compare strings n
 * @a: string a
 * @b: string b
 * @n: count
 * Return: diff
 */
int s_ncmp(const char *a, const char *b, size_t n)
{
	size_t i;

	if (n == 0)
	{
		return (0);
	}
	if (a == NULL || b == NULL)
	{
		return (a == b) ? 0 : (a ? 1 : -1);
	}
	i = 0;
	while (i < n && a[i] && b[i])
	{
		if (a[i] != b[i])
		{
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		}
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

/**
 * s_chr - find char in string
 * @s: input string
 * @c: char
 * Return: pointer or NULL
 */
char *s_chr(const char *s, int c)
{
	size_t i;

	if (s == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (c == '\0')
	{
		return ((char *)(s + i));
	}
	return (NULL);
}
