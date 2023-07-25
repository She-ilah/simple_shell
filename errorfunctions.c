#include "shell.h"

/**
 * str_to_int - Function converts a string to an integer.
 * @str: String to be converted.
 * Return: Returns 0 upon success or -1 upon failure.
 */
int str_to_int(char *str)
{
	int n = 0;
	unsigned long int integer = 0;

	if (*str == '+')
		str++;
	for (n = 0;  str[n] != '\0'; n++)
	{
		if (str[n] >= '0' && str[n] <= '9')
		{
			integer *= 10;
			integer += (str[n] - '0');
			if (integer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (integer);
}

/**
 * shell_printf_err - Function prints an error message to buffer.
 * @check: Parameter one.
 * @errstr: The main error string
 * Return: void.
 */
void shell_printf_err(info_t *check, char *errstr)
{
	shell_puts(check->fname);
	shell_puts(": ");
	print_d(check->line_count, STDERR_FILENO);
	shell_puts(": ");
	shell_puts(check->argv[0]);
	shell_puts(": ");
	shell_puts(errstr);
}

/**
 * shell_printf_dec - Function prints decimals to the buffer.
 * @input: input decimal.
 * @place: Place to write to.
 * Return: Function returns number of characters printed to place.
 */
int shell_printf_dec(int input, int place)
{
	int (*__putchar)(char) = _putchar;
	int n, check = 0;
	unsigned int val, start;

	if (place == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		val = -input;
		__putchar('-');
		check++;
	}
	else
		val = input;
	start = val;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (val / n)
		{
			__putchar('0' + start / n);
			check++;
		}
		start %= n;
	}
	__putchar('0' + start);
	check++;

	return (check);
}

/**
 * shell_con - Function converts numbers.
 * @num: number to be converted.
 * @base: base of the number
 * @fl: flag specifier.
 * Return: Function returns converted strings
 */
char *shell_con(long int num, int base, int fl)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(fl & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * shell_prep - Function removes all comments(preprocessor function)
 * @buffer: String to be modified.
 * Return: void
 */
void shell_prep(char *buffer)
{
	int n;

	for (n = 0; buffer[n] != '\0'; n++)
		if (buffer[n] == '#' && (!n || buffer[n - 1] == ' '))
		{
			buffer[n] = '\0';
			break;
		}
}

