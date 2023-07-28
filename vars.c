#include "shell.h"

/**
 * is_chain - Function identifies chain delimiter.
 * @check: parameter one.
 * @buffer: buffer (main display).
 * @place: Buffer's current postion.
 * Return: Returns 1 upon success or 0 upon failure.
 */
int is_chain(info_t *check, char *buffer, size_t *place)
{
	size_t n = *place;

	if (buffer[n] == '|' && buffer[n + 1] == '|')
	{
		buffer[n] = 0;
		n++;
		check->cmd_buf_type = CMD_OR;
	}
	else if (buffer[n] == '&' && buffer[n + 1] == '&')
	{
		buffer[n] = 0;
		n++;
		check->cmd_buf_type = CMD_AND;
	}
	else if (buffer[n] == ';')
	{
		buffer[n] = 0;
		check->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*place = n;
	return (1);
}

/**
 * halt_chain - Function determines whether to continue chaining.
 * @check: parameter one.
 * @buffer: buffer(main display).
 * @place: Current position.
 * index: index
 * @len: The length of the buffer.
 * Return: Void
 */
void halt_chain(info_t *check, char *buffer, size_t *place, size_t index, size_t len)
{
	size_t n = *place;

	if (check->cmd_buf_type == CMD_AND)
	{
		if (check->status)
		{
			buffer[index] = 0;
			n = len;
		}
	}
	if (check->cmd_buf_type == CMD_OR)
	{
		if (!check->status)
		{
			buffer[index] = 0;
			n = len;
		}
	}
	*place = n;
}

/**
 * new_alias - Function replaces an alias in the tokenized string.
 * @check: parameter one.
 * Return: 1 on success or 0 upon failure.
 */
int new_alias(info_t *check)
{
	int n;
	list_t *list;
	char *place;

	for (n = 0; n < 10; n++)
	{
		list = pre_node(check->alias, check->argv[0], '=');
		if (!list)
			return (0);
		free(check->argv[0]);
		place = _strchr(list->str, '=');
		if (!place)
			return (0);
		place = _strdup(place + 1);
		if (!place)
			return (0);
		check->argv[0] = place;
	}
	return (1);
}

/**
 * new_vars - Function renews the vars in the newly tokenized string.
 * @check: parameter one.
 * Return: Returns 1 on success or 0 upon failure.
 */
int new_vars(info_t *check)
{
	int n = 0;
	list_t *list;

	for (n = 0; check->argv[n]; n++)
	{
		if (check->argv[n][0] != '$' || !check->argv[n][1])
			continue;

		if (!_strcmp(check->argv[n], "$?"))
		{
			new_string(&(check->argv[n]),
					_strdup(shell_con(check->status, 10, 0)));
			continue;
		}
		if (!_strcmp(check->argv[n], "$$"))
		{
			new_string(&(check->argv[n]),
					_strdup(shell_con(getpid(), 10, 0)));
			continue;
		}
		list = pre_node(check->env, &check->argv[n][1], '=');
		if (list)
		{
			new_string(&(check->argv[n]),
					_strdup(_strchr(list->str, '=') + 1));
			continue;
		}
		new_string(&check->argv[n], _strdup(""));
	}
	return (0);
}

/**
 * new_string - Function replaces an old string.
 * @old_str: String to be replaced.
 * @new_str: new string
 * Return: 1 if replaced on success or 0 upon failure.
 */
int new_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
