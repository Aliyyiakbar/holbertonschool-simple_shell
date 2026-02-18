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
	char *pe;
	char *pc;
	char *tok;
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

	pe = get_env_path();
	if (pe == NULL)
	{
		return (NULL);
	}

	pc = str_duplicate(pe);
	if (pc == NULL)
	{
		return (NULL);
	}

	found = NULL;
	tok = strtok(pc, ":");
	while (tok)
	{
		full = build_path(tok, cmd);
		if (full && access(full, X_OK) == 0)
		{
			if (found)
			{
				free(found);
			}
			free(pc);
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
		tok = strtok(NULL, ":");
	}

	free(pc);
	return (found);
}
