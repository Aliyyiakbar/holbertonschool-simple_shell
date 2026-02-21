#include "bash.h"

/**
 * env_idx - find env index
 * @n: name
 * Return: index or -1
 */
int env_idx(char *n)
{
	size_t ln;
	int i;

	if (environ == NULL)
	{
		return (-1);
	}
	ln = s_len(n);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (s_ncmp(environ[i], n, ln) == 0 && environ[i][ln] == '=')
		{
			return (i);
		}
	}
	return (-1);
}
