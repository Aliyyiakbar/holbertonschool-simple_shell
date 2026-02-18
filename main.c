#include "bash.h"

int main(int argc, char **argv)
{
	(void)argc;

	return (shell_loop(argv));
}
