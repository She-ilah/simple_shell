#include "shell.h"

/**
 * init_info - Function initializes info_t struct in used functions.
 * @info: The address of struct.
 * Return: void.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * shell_info - Function sets the info_t struct used in functions.
 * @info: The address of struct.
 * @curr_argv: argument vector
 * Return: void
 */
void shell_info(info_t *info, char **curr_argv)
{
	int n = 0;

	info->fname = curr_argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n]; n++)
			;
		info->argc = n;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * shell_free_info - Function frees the used info_t struct.
 * @info: parameter one.
 * @total: Frees all the info_t struct.
 * Return: void.
 */
void shell_free_info(info_t *info, int total)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (total)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		free_ptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

