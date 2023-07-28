#include "shell.h"

/**
 * _memset- fills memory area pointed to by @s with
 * the constant byte.
 * @mem: the pointer to the memory area
 * @byte: the byte to fill the memory area with
 * @size: the amount of bytes to be filled
 * Return: a pointer to the memory area @s
 */
char *_memset(char *mem, char byte, unsigned int size)
{
	unsigned int n;

	for (n = 0; n < size; n++)
		mem[n] = byte;
	return (mem);
}

/**
 * ffree - Frees an array of strings and the array itself.
 * @arr: Array of strings.
 *
 * This function frees each individual string in the array @pp and then frees
 * the array itself.
 */

void ffree(char **arr)
{
	char **curr_ptr = arr;

	if (!arr)
		return;
	while (*arr)
	{
		free(*arr++);
	}
	free(curr_ptr);
}

/**
 * my_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previously allocated block.
 * @old_size: Size of the previous block in bytes.
 * @new_size: Size of the new block in bytes.
 * Return: Pointer to the reallocated memory block.
 */

void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *place;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	place = malloc(new_size);
	if (!place)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		place[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (place);
}
