#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @str: The string whose length is to be determined.
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
 * @str_one: The first string to compare.
 * @str_two: The second string to compare.
 * Return: An integer representing the comparison result(-, + or 0)
 */
int _strcmp(char *str_one, char *str_two)
{
	while (*str_one && *str_two)
	{
		if (*str_one != *str_two)
			return (*str_one - *str_two);
		str_one++;
		str_two++;
	}
	if (*str_one == *str_two)
		return (0);
	else
		return (*str_one < *str_two ? -1 : 1);
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
	*destinat = '\0';
		return (result);
}

/**
 * starts_with - function checks index of string.
 * @haystack: string to search for needle.
 * @needle: string to be found.
 * Return: Returns next haystack or NULL upon failure.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

