#include "shell.h"

/**
 * _strlen - Calculate the length of a string
 * @s: String to measure
 *
 * Return: Length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	if (s == NULL)
		return (0);

	while (s[len] != '\0')
		len++;

	return (len);
}

/**
 * _strdup - Duplicate a string
 * @str: String to duplicate
 *
 * Return: Pointer to new string, or NULL on failure
 */
char *_strdup(char *str)
{
	char *dup = NULL;
	int len = 0;
	int i = 0;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		dup[i] = str[i];

	return (dup);
}

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 0 if equal, difference otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (s1 == NULL || s2 == NULL)
		return (-1);

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}

/**
 * _strcat - Concatenate two strings
 * @dest: Destination string
 * @src: Source string to append
 *
 * Return: Pointer to destination string
 */
char *_strcat(char *dest, char *src)
{
	int dest_len = 0;
	int i = 0;

	if (dest == NULL || src == NULL)
		return (dest);

	dest_len = _strlen(dest);

	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';

	return (dest);
}
