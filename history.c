#include "shell.h"

/**
 * get_history - Function gets the history file of a file.
 * @check: parameter one.
 * Return: Returns the pointer that contains the history file.
 */

char *get_history(info_t *check)
{
	char *buffer;
	char *dir;

	dir = _getenv(check, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * shell_write_hist - Function creates or modifies a file.
 * @check: parameter one.
 * Return: Returns 1 on success or -1 upon failure.
 */
int shell_write_hist(info_t *check)
{
	ssize_t input;
	char *filename = get_history(check);
	list_t *list = NULL;

	if (!filename)
		return (-1);

	input = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (input == -1)
		return (-1);
	for (list = check->history; list; list = list->next)
	{
		_putsfd(list->str, input);
		_putfd('\n', input);
	}
	_putfd(BUF_FLUSH, input);
	close(input);
	return (1);
}

/**
 * shell_rhist - Function reads a files history.
 * @check: parameter one
 * Return: Files history on success or 0 upon failure.
 */
int shell_rhist(info_t *check)
{
	int n, last = 0, linecount = 0;
	ssize_t input, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history(check);

	if (!filename)
		return (0);

	input = open(filename, O_RDONLY);
	free(filename);
	if (input == -1)
		return (0);
	if (!fstat(input, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(input, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(input);
	for (n = 0; n < fsize; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			build_history_list(check, buffer + last, linecount++);
			last = n + 1;
		}
	if (last != n)
		build_history_list(check, buffer + last, linecount++);
	free(buffer);
	check->histcount = linecount;
	while (check->histcount-- >= HIST_MAX)
		delete_node_at_index(&(check->history), 0);
	renumber_history(check);
	return (check->histcount);
}

/**
 * append_history - Function appends strings to a history linked list.
 * @check: parameter one.
 * @buffer: buffer main display.
 * @count: Number of lines in history.
 * Return: Returns 0 on success.
 */
int append_history(info_t *check, char *buffer, int count)
{
	list_t *list = NULL;

	if (check->history)
		list = check->history;
	add_node_end(&list, buffer, count);

	if (!check->history)
		check->history = list;
	return (0);
}

/**
 * sort_history - Function sorts the history of a appended linked list.
 * @check: parameter one.
 * Return: Returns the newly appened count of the history file.
 */
int sort_history(info_t *check)
{
	list_t *list = check->history;
	int n = 0;

	while (list)
	{
		list->num = n++;
		list = list->next;
	}
	return (check->histcount = n);
}

