#include "shell.h"

/**
 * shell_ret_env - Function returns a copy of the environment.
 * @check: parameter one.
 * Return: Function returns 0 upon success.
 */
char **shell_ret_env(info_t *check)
{
	if (!check->environ || check->env_changed)
	{
		check->environ = list_to_strings(check->env);
		check->env_changed = 0;
	}
	return (check->environ);
}

/**
 * shell_rev_env - Function unsets an environment variable.
 * @check: parameter one.
 * @main_str: the string used in the function.
 * Return: Return 1 on success or 0 upon failure.
 */
int shell_rev_env(info_t *check, char *main_str)
{
	list_t *list = check->env;
	size_t n = 0;
	char *place;

	if (!list || !main_str)
		return (0);

	while (list)
	{
		place = starts_with(list->str, main_str);
		if (place && *place == '=')
		{
			check->env_changed = delete_node_at_index(&(check->env), n);
			n = 0;
			list = check->env;
			continue;
		}
		list = list->next;
		n++;
	}
	return (check->env_changed);
}

/**
 * shell_init_env - Function creates or modifies a new environment.
 * @check: parameter one.
 * @main_str: String used in function.
 * @value: Value of the environments variable.
 * Return: Returns 0 upon success.
 */
int shell_init_env(info_t *check, char *main_str, char *value)
{
	char *buffer = NULL;
	list_t *list;
	char *place;

	if (!main_str || !value)
		return (0);

	buffer = malloc(_strlen(main_str) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, main_str);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	list = check->env;
	while (list)
	{
		place = starts_with(list->str, main_str);
		if (place && *place == '=')
		{
			free(list->str);
			list->str = buffer;
			check->env_changed = 1;
			return (0);
		}
		list = list->next;
	}
	add_node_end(&(check->env), buffer, 0);
	free(buffer);
	check->env_changed = 1;
	return (0);
}

