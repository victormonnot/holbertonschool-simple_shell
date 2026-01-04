#include "shell.h"

/**
 * run_child - Execute command in child process
 * @cmd_path: Full path to command
 * @args: Array of arguments
 * @env: Environment variables
 */
void run_child(char *cmd_path, char **args, char **env)
{
	if (execve(cmd_path, args, env) == -1)
	{
		perror(args[0]);
		free(cmd_path);
		exit(127);
	}
}

/**
 * execute_cmd - Execute a command
 * @args: Array of arguments
 * @env: Environment variables
 * @prog_name: Name of the shell program
 * @line_count: Current line number
 *
 * Return: 0 on success, -1 to exit shell, 127 on command not found
 */
int execute_cmd(char **args, char **env, char *prog_name, int line_count)
{
	char *cmd_path = NULL;
	pid_t pid;
	int status;

	if (is_builtin(args[0]))
		return (handle_builtin(args, env));

	cmd_path = find_command(args[0], env);
	if (cmd_path == NULL)
	{
		print_error(prog_name, line_count, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}

	if (pid == 0)
		run_child(cmd_path, args, env);

	wait(&status);
	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (0);
}
