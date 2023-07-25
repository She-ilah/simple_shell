#include "shell.h"

/**
 * shell_puts - Funtion prints a string(error).
 * @str: String to be printed.(error)
 * Return: void.
 */
void shell_puts(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		shell_putchar(str[n]);
		n++;
	}
}

/**
 * shell_putchar - Function prints c to standard error.
 * @c: Character to be printed.
 * Return: Function returns 1 on success or -1 upon failure.
 */
int shell_putchar(char c)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}

/**
 * shell_putstwo - Function writes the character c to given input.
 * @c: Character to be printed.
 * @input: given input to be written to.
 * Return: Function returns 1 on success or -1 upon failure.
 */
int shell_putstwo(char c, int input)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(input, buffer, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buffer[n++] = c;
	return (1);
}

/**
 * shell_putstwo2 - Function prints number of chars in input string.
 * @str: String to be printed
 * @input: input to write to
 * Return: Total number of characters
 */
int shell_putstwo2(char *str, int input)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += shell_putstwo(*str++, input);
	}
	return (n);
}

