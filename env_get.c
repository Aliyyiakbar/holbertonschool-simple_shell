#include "bash.h"

/**
 * env_get - get env value
 * @n: name
 * Return: value or NULL
 */
char *env_get(const char *n)
{
	size_t ln;
	int i;

	if (n == NULL || n[0] == '\0' || environ == NULL)
	{
		return (NULL);
	}
	ln = s_len(n);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (s_ncmp(environ[i], n, ln) == 0 && environ[i][ln] == '=')
		{
			return (environ[i] + ln + 1);
		}
	}
	return (NULL);
}
