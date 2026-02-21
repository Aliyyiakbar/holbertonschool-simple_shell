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
	int st;

	if (ac > 2)
	{
		fprintf(stderr, "Usage: %s [filename]\n", av[0]);
		return (1);
	}

	h_load();
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
			h_save();
			h_free();
			env_free();
			a_free();
			return (127);
		}
		st = sh(av, fd);
		close(fd);
		h_save();
		h_free();
		env_free();
		a_free();
		return (st);
	}

	st = sh(av, STDIN_FILENO);
	h_save();
	h_free();
	env_free();
	a_free();
	return (st);
}
