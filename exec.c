#include "bash.h"

/**
 * opv - operator code
 * @s: token
 * Return: code
 */
static int opv(char *s)
{
	if (s == NULL)
	{
		return (0);
	}
	if (s_cmp(s, ";") == 0)
	{
		return (1);
	}
	if (s_cmp(s, "&&") == 0)
	{
		return (2);
	}
	if (s_cmp(s, "||") == 0)
	{
		return (3);
	}
	return (0);
}

/**
 * dup_av - duplicate argv slice
 * @t: tokens
 * @s: start
 * @e: end
 * Return: argv or NULL
 */
static char **dup_av(char **t, int s, int e)
{
	char **av;
	int i;
	int n;

	n = e - s;
	av = malloc(sizeof(char *) * (n + 1));
	if (av == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < n; i++)
	{
		av[i] = sdup(t[s + i]);
		if (av[i] == NULL)
		{
			av[i] = NULL;
			frev(av);
			return (NULL);
		}
	}
	av[n] = NULL;
	return (av);
}

/**
 * do_cmd - run one command
 * @av: argv array
 * @pr: program name
 * @ln: line number
 * @st: status pointer
 * Return: 1 to exit
 */
static int do_cmd(char **av, char *pr, int ln, int *st)
{
	int br;

	br = b_run(av, st, pr, ln);
	if (br == BUILTIN_EXIT)
	{
		return (1);
	}
	if (br == BUILTIN_HANDLED)
	{
		return (0);
	}
	run(av, pr, ln, st);
	return (0);
}

/**
 * run_seg - run argv slice
 * @t: tokens
 * @i: start
 * @j: end
 * @pr: program name
 * @ln: line number
 * @st: status pointer
 * @op: operator
 * Return: 1 to exit
 */
static int run_seg(char **t, int i, int j, char *pr, int ln, int *st, int op)
{
	char **av;

	av = dup_av(t, i, j);
	if (av == NULL)
	{
		return (0);
	}
	av = a_expa(av);
	vrep(av, *st);
	if (op == 2 && *st != 0)
	{
		frev(av);
		return (0);
	}
	if (op == 3 && *st == 0)
	{
		frev(av);
		return (0);
	}
	if (do_cmd(av, pr, ln, st))
	{
		frev(av);
		return (1);
	}
	frev(av);
	return (0);
}

/**
 * exec_ln - execute line
 * @buf: input line
 * @pr: program name
 * @st: status pointer
 * @ln: line number
 * Return: 1 to exit
 */
int exec_ln(char *buf, char *pr, int *st, int ln)
{
	char **t;
	int i;
	int j;
	int op;

	t = spl(buf, NULL);
	if (t == NULL || t[0] == NULL)
	{
		frev(t);
		return (0);
	}
	h_add(buf);
	op = 0;
	i = 0;
	while (t[i])
	{
		j = i;
		while (t[j] && !opv(t[j]))
		{
			j++;
		}
		if (j > i && run_seg(t, i, j, pr, ln, st, op))
		{
			frev(t);
			return (1);
		}
		if (t[j] == NULL)
		{
			break;
		}
		op = opv(t[j]);
		i = j + 1;
	}
	frev(t);
	return (0);
}
