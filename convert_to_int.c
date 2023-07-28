#include "shell.h"

/**
 * shell_on - Function checks if the shell is in interactive mode.
 * @str_addr: Parameter one.
 * Return: True(1) if shell is in interactive mode or 0 upon failure.
 */
int shell_on(info_t *str_addr)
{
	/*Provision to determine whether shell is interactive*/
	return (isatty(STDIN_FILENO) && str_addr->readfd <= 2);
}

/**
 * char_split - Function checks if char seperates strings(delimiter).
 * @check: The char to be checked.
 * @str: the delimeter string
 * Return: 1 if true or 0 upon failure
 */
int char_split(char check, char *str)
{
	/*Goes through the string.*/
	while (*str)
		if (*str++ == check)
			return (1);
	return (0);
}

/**
 * is_letter - Function checks for letters in strings.
 * @check: The char to be checked
 * Return: 1 if char is identified or 0 upon failure.
 */
int is_letter(int check)
{
	/*If char is a letter function returns 1*/
	if ((check >= 'a' && check <= 'z') || (check >= 'A' && check <= 'Z'))
	{
		return (1);
	}
	else
		/*Returns 0 if it goes wrong*/
		return (0);
}

/**
 * convert_to_int - Function converts a string to an integer
 * @str: the string to be converted to integer.
 * Return: 0 if no numbers in string or converted number.
 */
int convert_to_int(char *str)
{
	int n, sign = 1, fl = 0, integer;
	unsigned int res = 0;

	/*Goes through the string*/
	for (n = 0; str[n] != '\0' && fl != 2; n++)
	{
		if (str[n] == '-')
			sign *= -1;

		if (str[n] >= '0' && str[n] <= '9')
		{
			fl = 1;
			res *= 10;
			res += (str[n] - '0');
		}
		else if (fl == 1)
			fl = 2;
	}
	if (sign == -1)
		integer = -res;
	else
		integer = res;

	return (integer);
}

