#include "bash.h"

/**
 * av_len - argv length
 * @av: argv array
 * Return: length
 */
static int av_len(char **av)
{
	int n;

	for (n = 0; av && av[n]; n++)
	{
	}
	return (n);
}

/**
 * av_copy - copy argv
 * @dst: dst array
 * @src: src array
 * @off: offset
 * @skip: skip count
 * Return: next index or -1
 */
static int av_copy(char **dst, char **src, int off, int skip)
{
	int i;
	int j;

	for (i = skip, j = 0; src[i]; i++, j++)
	{
		dst[off + j] = sdup(src[i]);
		if (dst[off + j] == NULL)
		{
			dst[off + j] = NULL;
			return (-1);
		}
	}
	return (off + j);
}

/**
 * a_exp - expand alias
 * @av: argv array
 * Return: argv array
 */
char **a_exp(char **av)
{
	char **tv;
	char **nv;
	char *v;
	int n1;
	int n2;
	int n;

	v = a_get(av[0]);
	if (v == NULL)
	{
		return (av);
	}
	tv = spl(v, NULL);
	if (tv == NULL || tv[0] == NULL)
	{
		frev(tv);
		return (av);
	}
	n1 = av_len(tv);
	n2 = av_len(av);
	nv = malloc(sizeof(char *) * (n1 + n2));
	if (nv == NULL)
	{
		frev(tv);
		return (av);
	}
	n = av_copy(nv, tv, 0, 0);
	if (n < 0 || av_copy(nv, av, n, 1) < 0)
	{
		frev(nv);
		frev(tv);
		return (av);
	}
	nv[n1 + n2 - 1] = NULL;
	frev(tv);
	frev(av);
	return (nv);
}

/**
 * a_expa - expand alias repeatedly
 * @av: argv array
 * Return: argv array
 */
char **a_expa(char **av)
{
	char **old;
	int k;

	k = 0;
	while (av && av[0] && a_get(av[0]) && k < 10)
	{
		old = av;
		av = a_exp(av);
		if (av == old)
		{
			break;
		}
		k++;
	}
	return (av);
}
