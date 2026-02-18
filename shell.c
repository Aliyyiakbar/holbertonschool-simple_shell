#include "bash.h"

static int g_interactive;

int is_interactive(void)
{
	return (g_interactive);
}

void sigint_handler(int sig)
{
	(void)sig;

	if (g_interactive)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
	}
}

static int execute_command(char **args, char *prog, int line_num, int *status)
{
	pid_t pid;
	int wstatus;
	char *path;

	path = resolve_path(args[0]);
	if (path == NULL)
	{
		print_error(prog, line_num, args[0]);
		*status = 127;
		return (0);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(path, args, environ);
		if (errno == EACCES)
		{
			fprintf(stderr, "%s: %d: %s: Permission denied\n",
				prog, line_num, args[0]);
		}
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog, line_num, args[0]);
		}
		free(path);
		exit(126);
	}
	else if (pid < 0)
	{
		perror(prog);
		*status = 1;
	}
	else
	{
		if (waitpid(pid, &wstatus, 0) == -1)
		{
			perror(prog);
			*status = 1;
		}
		else if (WIFEXITED(wstatus))
		{
			*status = WEXITSTATUS(wstatus);
		}
		else
		{
			*status = 1;
		}
	}

	free(path);
	return (0);
}

int shell_loop(char **argv)
{
	char *line;
	size_t len;
	ssize_t nread;
	char **args;
	int status;
	int line_num;
	int builtin_ret;

	line = NULL;
	len = 0;
	status = 0;
	line_num = 0;

	g_interactive = isatty(STDIN_FILENO);
	signal(SIGINT, sigint_handler);

	while (1)
	{
		if (g_interactive)
		{
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		}

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (g_interactive)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}

		line_num++;
		if (is_blank(line))
		{
			continue;
		}

		args = split_line(line, NULL);
		if (args == NULL || args[0] == NULL)
		{
			free_args(args);
			continue;
		}

		builtin_ret = handle_builtin(args, &status);
		if (builtin_ret == BUILTIN_EXIT)
		{
			free_args(args);
			break;
		}
		if (builtin_ret == BUILTIN_HANDLED)
		{
			free_args(args);
			continue;
		}

		execute_command(args, argv[0], line_num, &status);
		free_args(args);
	}

	free(line);
	return (status);
}
