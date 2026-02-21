#include "bash.h"

/**
 * a_free - free aliases
 * Return: void
 */
void a_free(void)
{
	int i;

	for (i = 0; i < a_sz; i++)
	{
		free(a_n[i]);
		free(a_v[i]);
	}
	free(a_n);
	free(a_v);
	a_n = NULL;
	a_v = NULL;
	a_sz = 0;
	a_cap = 0;
}
