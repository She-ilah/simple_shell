#include "shell.h"

/**
 * shell_history - Function replicates shell history builtin.
 * @check: Parameter one.
 * Return: Function returns 0 upon success.
 */
int shell_history(info_t *check)
{
	shell_printf_list(check->history);
	return (0);
}

/**
 * rev_init_alias - Function uninitializes alias to a string
 * @check: parameter one
 * @str: String alias is initialized to.
 * Return: Function returns 0 on success or 1 upon failure.
 */
int rev_init_alias(info_t *check, char *str)
{
	char *place, count;
	int rev;

	place = _strchr(str, '=');
	if (!place)
		return (1);
	count = *place;
	*place = 0;
	rev = rm_node(&(check->alias),
		index_node(check->alias, pre_node(check->alias, str, -1)));
	*place = count;
	return (rev);
}

/**
 * init_alias - Funtion initializes alias to a string.
 * @check: parameter one
 * @str: String alias is initialized to.
 * Return: Function returns 0 on success or 1 upon failure.
 */
int init_alias(info_t *check, char *str)
{
	char *place;

	place = _strchr(str, '=');
	if (!place)
		return (1);
	if (!*++place)
		return (rev_init_alias(check, str));

	rev_init_alias(check, str);
	return (append_list(&(check->alias), str, 0) == NULL);
}

/**
 * printf_shell_alias - Function prints an alias string to buffer.
 * @list: Parameter one(node).
 * Return: Function returns 0 on success or 1 upon failure.
 */
int printf_shell_alias(list_t *list)
{
	char *place = NULL, *n = NULL;

	if (list)
	{
		place = _strchr(list->str, '=');
		for (n = list->str; n <= place; n++)
		_putchar(*n);
		_putchar('\'');
		_puts(place + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - Replica of the shell alias builtin function.
 * @check: Prototype one.
 * Return: Function returns 0 on success.
 */
int shell_alias(info_t *check)
{
	int n = 0;
	char *c = NULL;
	list_t *list = NULL;

	if (check->argc == 1)
	{
		list = check->alias;
		while (list)
		{
			printf_shell_alias(list);
			list = list->next;
		}
		return (0);
	}
	for (n = 1; check->argv[n]; n++)
	{
		c = _strchr(check->argv[n], '=');
		if (c)
			init_alias(check, check->argv[n]);
		else
			printf_shell_alias(pre_node(check->alias, check->argv[n], '='));
	}
	return (0);
}

