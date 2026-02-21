#include "bash.h"

#include <fcntl.h>

/**
 * main - entry point
 * @ac: argc
 * @av: argv
 * Return: status
 */
int main(int ac, char **av)
{
	int fd;

	if (ac > 2)
	{
		fprintf(stderr, "Usage: %s [filename]\n", av[0]);
		return (1);
	}

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
			return (127);
		}
		return (sh(av, fd));
	}

	return (sh(av, STDIN_FILENO));
}
