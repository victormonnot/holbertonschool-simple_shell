#include "shell.h"

/**
 * get_path - Get the PATH variable from environment
 * @env: Environment variables
 *
 * Return: Pointer to PATH value, or NULL if not found
 */
char *get_path(char **env)
{
	int i = 0;

	if (env == NULL)
		return (NULL);

	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}

	return (NULL);
}

/**
 * build_path - Build full path by concatenating dir and command
 * @dir: Directory path
 * @cmd: Command name
 *
 * Return: Full path string, or NULL on failure
 */
char *build_path(char *dir, char *cmd)
{
	char *full_path = NULL;
	int dir_len = 0;
	int cmd_len = 0;

	dir_len = _strlen(dir);
	cmd_len = _strlen(cmd);

	full_path = malloc(dir_len + cmd_len + 2);
	if (full_path == NULL)
		return (NULL);

	full_path[0] = '\0';
	_strcat(full_path, dir);
	_strcat(full_path, "/");
	_strcat(full_path, cmd);

	return (full_path);
}

/**
 * search_in_path - Search for command in PATH directories
 * @cmd: Command to search for
 * @path: PATH string
 *
 * Return: Full path if found, NULL otherwise
 */
char *search_in_path(char *cmd, char *path)
{
	char *path_copy = NULL;
	char *dir = NULL;
	char *full_path = NULL;
	struct stat st;

	path_copy = _strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = build_path(dir, cmd);
		if (full_path != NULL && stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * find_command - Find the full path of a command
 * @cmd: Command to find
 * @env: Environment variables
 *
 * Return: Full path if found, NULL otherwise
 */
char *find_command(char *cmd, char **env)
{
	char *path = NULL;
	struct stat st;

	if (cmd == NULL || cmd[0] == '\0')
		return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &st) == 0)
			return (_strdup(cmd));
		return (NULL);
	}

	path = get_path(env);
	if (path == NULL)
		return (NULL);

	return (search_in_path(cmd, path));
}
