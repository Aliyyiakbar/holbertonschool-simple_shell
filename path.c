#include "bash.h"

static char *get_env_path(void)
{
	int i;
	size_t len;

	len = strlen("PATH=");
	if (environ == NULL)
	{
		return (NULL);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", len) == 0)
		{
			return (environ[i] + len);
		}
	}

	return (NULL);
}

static char *build_path(const char *dir, const char *cmd)
{
	size_t len;
	char *full;

	len = strlen(dir) + strlen(cmd) + 2;
	full = malloc(len);
	if (full == NULL)
	{
		return (NULL);
	}

	sprintf(full, "%s/%s", dir, cmd);
	return (full);
}

char *resolve_path(char *cmd)
{
	char *path_env;
	char *path_copy;
	char *token;
	char *full;
	char *found;

	if (cmd == NULL || cmd[0] == '\0')
	{
		return (NULL);
	}

	if (contains_slash(cmd))
	{
		if (access(cmd, X_OK) == 0 || access(cmd, F_OK) == 0)
		{
			return (str_duplicate(cmd));
		}
		return (NULL);
	}

	path_env = get_env_path();
	if (path_env == NULL)
	{
		return (NULL);
	}

	path_copy = str_duplicate(path_env);
	if (path_copy == NULL)
	{
		return (NULL);
	}

	found = NULL;
	token = strtok(path_copy, ":");
	while (token)
	{
		full = build_path(token, cmd);
		if (full && access(full, X_OK) == 0)
		{
			if (found)
			{
				free(found);
			}
			free(path_copy);
			return (full);
		}
		if (full && access(full, F_OK) == 0 && found == NULL)
		{
			found = full;
		}
		else
		{
			free(full);
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (found);
}
