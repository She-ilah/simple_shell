#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @str: The string whose length is to be determined.
 *
 * Return: The length of the string.
 */
int _strlen(char *str)
{
	int length = 0;

	if (!str)
		return (0);
	while (*str++)
		length++;
	return (length);
}
/**
 * _strcmp - Performs alphabetical comparison of two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 *
 * Return: An integer representing the comparison result(-, + or 0)
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
 * _strcat - Concatenates two strings.
 * @destinat: The destination buffer to store the concatenated string.
 * @source: The source buffer, whose content will be appended.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strcat(char *destinat, char *source)
{
	char *result = destinat;

	while (*destinat)
		destinat++;
	while (*source)
		*destinat++ = *source++;
	*destinat = '\0'
		return (result);
}
