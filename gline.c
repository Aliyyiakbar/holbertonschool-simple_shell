#include "bash.h"

/**
 * grow - grow buffer
 * @s: buffer
 * @cap: cap
 * @need: needed size
 * Return: buffer or NULL
 */
static char *grow(char *s, size_t *cap, size_t need)
{
	size_t nc;
	size_t i;
	char *n;

	nc = (*cap == 0) ? 128 : *cap;
	while (nc < need)
	{
		nc *= 2;
	}

	n = malloc(nc);
	if (n == NULL)
	{
		free(s);
		return (NULL);
	}

	for (i = 0; i < *cap; i++)
	{
		n[i] = s ? s[i] : 0;
	}

	free(s);
	*cap = nc;
	return (n);
}

/**
 * rfill - refill buffer
 * @fd: fd
 * @b: buf
 * @n: size
 * @i: index
 * Return: 0 eof, 1 retry, 2 ok
 */
static int rfill(int fd, char *b, int *n, int *i)
{
	*n = (int)read(fd, b, 1024);
	*i = 0;
	if (*n < 0 && errno == EINTR)
	{
		return (1);
	}
	if (*n <= 0)
	{
		return (0);
	}
	return (2);
}

/**
 * addc - add char to line
 * @s: buffer
 * @cap: cap
 * @len: len
 * @c: char
 * Return: 1 on ok
 */
static int addc(char **s, size_t *cap, size_t *len, char c)
{
	if (*len + 2 > *cap)
	{
		*s = grow(*s, cap, *len + 2);
		if (*s == NULL)
		{
			return (0);
		}
	}
	(*s)[(*len)++] = c;
	return (1);
}

/**
 * gl - read one line from fd
 * @fd: file descriptor
 * Return: line or NULL
 */
char *gl(int fd)
{
	static char b[1024];
	static int n, i;
	char *s;
	size_t cap, len;
	int r;

	s = NULL;
	cap = 0;
	len = 0;
	while (1)
	{
		if (i >= n)
		{
			r = rfill(fd, b, &n, &i);
			if (r == 1)
			{
				continue;
			}
			if (r == 0)
			{
				break;
			}
		}
		if (!addc(&s, &cap, &len, b[i++]))
		{
			return (NULL);
		}
		if (s[len - 1] == '\n')
		{
			break;
		}
	}
	if (len == 0)
	{
		free(s);
		return (NULL);
	}
	s[len] = '\0';
	return (s);
}
