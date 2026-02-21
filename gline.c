#include "bash.h"

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
	char c;

	s = NULL;
	cap = 0;
	len = 0;
	while (1)
	{
		if (i >= n)
		{
			n = (int)read(fd, b, sizeof(b));
			i = 0;
			if (n <= 0)
			{
				break;
			}
		}
		c = b[i++];
		if (len + 2 > cap)
		{
			s = grow(s, &cap, len + 2);
			if (s == NULL)
			{
				return (NULL);
			}
		}
		s[len++] = c;
		if (c == '\n')
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
