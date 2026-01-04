#include "shell.h"

/**
 * read_line - Read a line from stdin
 *
 * Return: Pointer to the line read, or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read_len;

	read_len = getline(&line, &bufsize, stdin);

	if (read_len == -1)
	{
		free(line);
		return (NULL);
	}

	if (read_len > 0 && line[read_len - 1] == '\n')
		line[read_len - 1] = '\0';

	return (line);
}

/**
 * count_tokens - Count number of tokens in a string
 * @line: String to count tokens in
 *
 * Return: Number of tokens
 */
int count_tokens(char *line)
{
	int count = 0;
	char *copy = NULL;
	char *token = NULL;

	copy = _strdup(line);
	if (copy == NULL)
		return (0);

	token = strtok(copy, " \t\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}

	free(copy);
	return (count);
}

/**
 * split_line - Split a line into tokens
 * @line: Line to split
 *
 * Return: Array of tokens, or NULL on failure
 */
char **split_line(char *line)
{
	char **args = NULL;
	char *token = NULL;
	int num_tokens = 0;
	int i = 0;

	num_tokens = count_tokens(line);
	if (num_tokens == 0)
		return (NULL);

	args = malloc(sizeof(char *) * (num_tokens + 1));
	if (args == NULL)
		return (NULL);

	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		args[i] = _strdup(token);
		if (args[i] == NULL)
		{
			free_array(args);
			return (NULL);
		}
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	return (args);
}
