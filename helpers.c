#include "shell.h"

/**
 * print_error - Print error message for command not found
 * @prog_name: Name of the shell program
 * @line_count: Current line number
 * @cmd: Command that was not found
 */
void print_error(char *prog_name, int line_count, char *cmd)
{
	fprintf(stderr, "%s: %d: %s: not found\n", prog_name, line_count, cmd);
}

/**
 * free_array - Free an array of strings
 * @array: Array to free
 */
void free_array(char **array)
{
	int i = 0;

	if (array == NULL)
		return;

	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
