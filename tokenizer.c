#include "shell.h"

/**
 * **strtow - Function tokenizes a string.
 * @str: The string to be tokenized.
 * @delim: Delimter string.
 * Return: Pointer to an array of strings or NULL upon failure.
 */

char **strtow(char *str, char *delim)
{
	int n, a, b, c, total = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!char_split(str[n], delim) && (char_split(str[n + 1], delim) || !str[n + 1]))
			total++;

	if (total == 0)
		return (NULL);
	string = malloc((1 + total) * sizeof(char *));
	if (!string)
		return (NULL);
	for (n = 0, a = 0; a < total; a++)
	{
		while (char_split(str[n], delim))
			n++;
		b = 0;
		while (!char_split(str[n + b], delim) && str[n + b])
			b++;
		string[a] = malloc((b + 1) * sizeof(char));
		if (!string[a])
		{
			for (b = 0; b < a; b++)
				free(string[b]);
			free(string);
			return (NULL);
		}
		for (c = 0; c < b; c++)
			string[a][c] = str[n++];
		string[a][c] = 0;
	}
	string[a] = NULL;
	return (string);
}

/**
 * **strtow2 - Function tokenizes a string.
 * @str: String to be tokenized.
 * @delim: delimiter
 * Return: Returns a pointer to an array of strings or NULL upon failure.
 */
char **strtow2(char *str, char delim)
{
	int n, a, b, c, total = 0;
	char **string;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		if ((str[n] != delim && str[n + 1] == delim) ||
				    (str[n] != delim && !str[n + 1]) || str[n + 1] == delim)
			total++;
	if (total == 0)
		return (NULL);
	string = malloc((1 + total) * sizeof(char *));
	if (!string)
		return (NULL);
	for (n = 0, a = 0; a < total; a++)
	{
		while (str[n] == delim && str[n] != delim)
			n++;
		b = 0;
		while (str[n + b] != delim && str[n + b] && str[n + b] != delim)
			b++;
		string[a] = malloc((b + 1) * sizeof(char));
		if (!string[a])
		{
			for (b = 0; b < a; b++)
				free(string[b]);
			free(string);
			return (NULL);
		}
		for (c = 0; c < b; c++)
			string[a][c] = str[n++];
		string[a][c] = 0;
	}
	string[a] = NULL;
	return (string);
}

