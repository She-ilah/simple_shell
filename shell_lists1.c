#include "shell.h"

/**
 * list_len - Function determines length of a linked list
 * @ptr: Pointer to the node.
 * Return: Returns the size of the linked list.
 */
size_t list_len(const list_t *ptr)
{
	size_t n = 0;

	while (ptr)
	{
		ptr = ptr->next;
		n++;
	}
	return (n);
}

/**
 * string_list - Function returns an array of strings of the l-list.
 * @ptr: Pointer to the head node.
 * Return: Returns an array of strings of the linked list.
 */
char **string_list(list_t *ptr)
{
	list_t *list = ptr;
	size_t hold = list_len(ptr), n;
	char **string;
	char *str;

	if (!ptr || !hold)
		return (NULL);
	string = malloc(sizeof(char *) * (hold + 1));
	if (!string)
		return (NULL);
	for (hold = 0; list; list = list->next, hold++)
	{
		str = malloc(_strlen(list->str) + 1);
		if (!str)
		{
			for (n = 0; n < hold; n++)
				free(string[n]);
			free(string);
			return (NULL);
		}

		str = _strcpy(str, list->str);
		string[hold] = str;
	}
	string[hold] = NULL;
	return (string);
}


/**
 * shell_printf_list - Function prints all elements of a linked list.
 * @ptr: Pointer to the list_t linked list.
 * Return: Returns the size of the linked list.
 */
size_t shell_printf_list(const list_t *ptr)
{
	size_t n = 0;

	while (ptr)
	{
		_puts(convert_number(ptr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		n++;
	}
	return (n);
}

/**
 * pre_node - Function returns a specified node.
 * @node: Pointer to specified node.
 * @pre: String to be used in function.
 * @c: the next character after parefix to match
 * Return: Returns an identical node or null upon failure.
 */
list_t *pre_node(list_t *node, char *pre, char c)
{
	char *place = NULL;

	while (node)
	{
		place = starts_with(node->str, pre);
		if (place && ((c == -1) || (*place == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * index_node - Function gets the index of a used node.
 * @ptr: Pointer to the head of the linked-list.
 * @node: Main pointer to the node.
 * Return: Returns the index of the node or -1 upon failure.
 */
ssize_t index_node(list_t *ptr, list_t *node)
{
	size_t n = 0;

	while (ptr)
	{
		if (ptr == node)
			return (n);
		ptr = ptr->next;
		n++;
	}
	return (-1);
}

