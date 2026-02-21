#include "bash.h"

/**
 * main - entry point
 * @ac: argc
 * @av: argv
 * Return: status
 */
int main(int ac, char **av)
{
	(void)ac;

	return (sh(av));
}
