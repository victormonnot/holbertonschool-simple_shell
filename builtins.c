#include "shell.h"

/**
 * is_builtin - Check if a command is a builtin
 * @cmd: Command to check
 *
 * Return: 1 if builtin, 0 otherwise
 */
int is_builtin(char *cmd)
{
	if (_strcmp(cmd, "exit") == 0)
		return (1);
	if (_strcmp(cmd, "env") == 0)
		return (1);

	return (0);
}

/**
 * handle_exit - Handle the exit builtin
 * @args: Arguments (unused for now)
 *
 * Return: -1 to signal shell exit
 */
int handle_exit(char **args)
{
	(void)args;
	return (-1);
}

/**
 * handle_env - Handle the env builtin
 * @env: Environment variables
 *
 * Return: 0 on success
 */
int handle_env(char **env)
{
	int i = 0;

	if (env == NULL)
		return (0);

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}

	return (0);
}

/**
 * handle_builtin - Handle builtin commands
 * @args: Array of arguments
 * @env: Environment variables
 *
 * Return: Result of the builtin command
 */
int handle_builtin(char **args, char **env)
{
	if (_strcmp(args[0], "exit") == 0)
		return (handle_exit(args));

	if (_strcmp(args[0], "env") == 0)
		return (handle_env(env));

	return (0);
}
