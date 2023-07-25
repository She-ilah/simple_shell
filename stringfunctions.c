#include "shell.h"

/**
 **_strncpy - Function copies a string(replica of strncpy).
 *@dest: String to be copied to.(destination)
 *@src: String to be copied.(source)
 *@n: Number of characters to be copied.
 *Return: The newly copied string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *new_str = dest;

	i = 0;
	/*Goes through characters of the string*/
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
		/*String is copied*/
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
			/*Adds null-terminater to end of copied string*/
		}
	}
	/*Returns copied string*/
	return (new_str);
}

/**
 **_strncat - Function concatenates two strings
 *@dest: String one to be concatenated.
 *@src: String two to be concatenated.
 *@bytes: Amount of bytes allocated to newly concatenated string.
 *Return: The newly concatenated string
 */
char *_strncat(char *dest, char *src, int bytes)
{
	int i, j;
	char *new_str = dest;

	i = 0;
	j = 0;
	/* As long as strings are not at the end*/
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < bytes)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	/*Concatenates the strings*/
	if (j < bytes)
		dest[i] = '\0';
	/*Add a null-terminator*/
	return (new_str);
}

/**
 **_strchr - Function finds a specific character in a string.
 *@str: The string to be searched.
 *@c: the character to find.
 *Return: Pointer to the new memory.
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');
	/* Searches the string*/

	return (NULL);
}

