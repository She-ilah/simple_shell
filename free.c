#include "shell.h"

/**
 * free_ptr - Function frees a pointer.
 * @ptr: Pointer to be freed.
 * Return: 1 upon success or 0 upon failure.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

