#include "shell.h"

/**
 * _strcpy - Function copies a string.
 * @dest: the destination string.
 * @src: the source string.
 * Return: Returns a pointer to destination string.
 */
char *_strcpy(char *dest, char *src)
{
	int n = 0;

	/*Function that copies a string*/
	if (dest == src || src == 0)
		return (dest);
	while (src[n])
	{
		dest[n] = src[n];
		n++;
		/*Copies a string to the dest*/
	}
	dest[n] = 0;
	return (dest);
}

/**
 * _strdup - Function duplicates a string.
 * @str: The string to be duplicated.
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *new_str;

	if (str == NULL)
		return (NULL);
	/*if the string is empty*/
	while (*str++)
		len++;
	new_str = malloc(sizeof(char) * (len + 1));
	/*Dynamically allocates memory using malloc*/
	if (!new_str)
		return (NULL);
	for (len++; len--;)
		new_str[len] = *--str;
	/*Duplicates the string*/
	return (new_str);
}

/**
 * _puts - Function prints an input string.
 * @str: The string to be printed
 * Return: void
 */
void _puts(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_putchar(str[n]);
		n++;
	}
	/* Functions to write on to buffer main display*/
}

/**
 * _putchar - Function writes the character c to standard output.
 * @c: The character to be printed.
 * Return: Returns 1 on success or -1 upon failure.
 */
int _putchar(char c)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	/*Functions to write on to buffer main display*/
	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}

