#include "shell.h"

/**
 * main - Entry point of the simple shell
 * @argc: Argument count (unused)
 * @argv: Argument vector
 * @env: Environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	char **args = NULL;
	int status = 0;
	int line_count = 0;
	int interactive = isatty(STDIN_FILENO);

	(void)argc;

	while (1)
	{
		if (interactive)
			printf("$ ");

		line = read_line();
		if (line == NULL)
		{
			if (interactive)
				printf("\n");
			break;
		}

		line_count++;

		args = split_line(line);
		if (args == NULL || args[0] == NULL)
		{
			free(line);
			free_array(args);
			continue;
		}

		status = execute_cmd(args, env, argv[0], line_count);

		free(line);
		free_array(args);

		if (status == -1)
			break;
	}
	return (0);
}
