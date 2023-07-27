#include "shell.h"

/**
 * _memset- fills memory area pointed to by @s with
 * the constant byte @b for @n bytes
 * @s: the pointer to the memory area
 * @b: the byte to fill the memory area with
 * @j: the amount of bytes to be filled
 * Return: a pointer to the memory area @s
 */
char *_memset(char *s, char b, unsigned int j)
{
	unsigned int i;

	for (i = 0; i < j; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Frees an array of strings and the array itself.
 * @pp: Array of strings.
 *
 * This function frees each individual string in the array @pp and then frees
 * the array itself.
 */

void ffree(char **pp)
{
	char **current_ptr = pp;

	if (!pp)
		return;
	while (*current_ptr)
	{
		free(*current_ptr);
		current_ptr++;
	}
	free(pp);
}

/**
 * my_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: Size of the previous block in bytes.
 * @new_size: Size of the new block in bytes.
 *
 * Return: Pointer to the reallocated memory block.
 */

void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
