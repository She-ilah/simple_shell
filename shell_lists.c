#include "shell.h"

/**
 * add_node - Function appends linked list from the beginning.
 * @ptr: Pointer to the node.
 * @str: str field of node
 * @num: index
 * Return: Function returns the size of list.
 */
list_t *add_node(list_t **ptr, const char *str, int num)
{
	list_t *new_ptr;

	if (!ptr)
		return (NULL);
	new_ptr = malloc(sizeof(list_t));
	if (!new_ptr)
		return (NULL);
	_memset((void *)new_ptr, 0, sizeof(list_t));
	new_ptr->num = num;
	if (str)
	{
		new_ptr->str = _strdup(str);
		if (!new_ptr->str)
		{
			free(new_ptr);
			return (NULL);
		}
	}
	new_ptr->next = *ptr;
	*ptr = new_ptr;
	return (new_ptr);
}

/**
 * append_list - Function adds a node to end of the linked-list.
 * @ptr: Pointer to the head node.
 * @str: String of the node.
 * @num: index
 * Return: Returns the size of the linked list.
 */
list_t *append_list(list_t **ptr, const char *str, int num)
{
	list_t *new_list, *list;

	if (!ptr)
		return (NULL);

	list = *ptr;
	new_list = malloc(sizeof(list_t));
	if (!new_list)
		return (NULL);
	_memset((void *)new_list, 0, sizeof(list_t));
	new_list->num = num;
	if (str)
	{
		new_list->str = _strdup(str);
		if (!new_list->str)
		{
			free(new_list);
			return (NULL);
		}
	}
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new_list;
	}
	else
		*ptr = new_list;
	return (new_list);
}

/**
 * shell_str - Function prints the string of a linked list.
 * @ptr: The pointer to the first node.
 * Return: Returns the size of the list.
 */
size_t shell_str(const list_t *ptr)
{
	size_t n = 0;

	while (ptr)
	{
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		n++;
	}
	return (n);
}

/**
 * rm_node - Function deletes node at specified index.
 * @ptr: pointer to the head node.
 * @index: index to be deleted.
 * Return: Returns 1 on success or 0 upon failure
 */
int rm_node(list_t **ptr, unsigned int index)
{
	list_t *list, *old_list;
	unsigned int n = 0;

	if (!ptr || !*ptr)
		return (0);

	if (!index)
	{
		list = *ptr;
		*ptr = (*ptr)->next;
		free(list->str);
		free(list);
		return (1);
	}
	list = *ptr;
	while (list)
	{
		if (n == index)
		{
			old_list->next = list->next;
			free(list->str);
			free(list);
			return (1);
		}
		n++;
		old_list = list;
		list = list->next;
	}
	return (0);
}

/**
 * free_list - Function frees all nodes of a linked-list.
 * @ptr: Pointer to the head node.
 * Return: void
 */
void free_list(list_t **ptr)
{
	list_t *list, *new_list, *head;

	if (!ptr || !*ptr)
		return;
	head = *ptr;
	list = head;
	while (list)
	{
		new_list = list->next;
		free(list->str);
		free(list);
		list = new_list;
	}
	*ptr = NULL;
}

