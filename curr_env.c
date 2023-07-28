#include "shell.h"

/**
 * shell_env - Function prints the current environment
 * @check: Parameter one.
 * Return: Function returns 0 on success.
 */
int shell_env(info_t *check)
{
	shell_str(check->env);
	return (0);
}

/**
 * shell_env_val - Function obtains the value of environment variable
 * @check: Parameter one.
 * @envir: Name of the environment variable
 * Return: Value of the environment variable.
 */
char *shell_env_val(info_t *check, const char *envir)
{
	list_t *list = check->env;
	char *place;

	while (list)
	{
		place = starts_with(list->str, envir);
		if (place && *place)
			return (place);
		list = list->next;
	}
	return (NULL);
}

/**
 * shell_set_env - Function sets a new environment or modifies one.
 * @check: Parameter one.
 * Return: Function returns 0 on success.
 */
int shell_set_env(info_t *check)
{
	if (check->argc != 3)
	{
		shell_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (shell_init_env(check, check->argv[1], check->argv[2]))
		return (0);
	return (1);
}

/**
 * shell_unset_env - Function unsets the environment variable
 * @check: parameter one.
 * Return: Function returns 0 on success.
 */
int shell_unset_env(info_t *check)
{
	int n;

	if (check->argc == 1)
	{
		shell_puts("Insufficient number of arguments.\n");
		return (1);
	}
	for (n = 1; n <= check->argc; n++)
		shell_rev_env(check, check->argv[n]);

	return (0);
}

/**
 * fill_env_list - Function fills the environment linked list.
 * @check: Parameter one.
 * Return: Function returns 0 on success.
 */
int fill_env_list(info_t *check)
{
	list_t *list = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		append_list(&list, environ[n], 0);
	check->env = list;
	return (0);
}

