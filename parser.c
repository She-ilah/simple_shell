#include "shell.h"

/**
 * is_cmd - Check if a file is an executable command.
 * @info: Pointer to the info struct.
 * @path: Path to the file.
 *
 * This function determines whether the given file at
 * the specified path is an
 * executable command.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;
	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Create a duplicate of characters from
 * @pathstr starting at @start
 * and ending at @stop (exclusive).
 * @pathstr: The PATH string.
 * @start: Starting index.
 * @stop: Stopping index (exclusive).
 *
 * This function creates a new buffer containing
 * the characters from @pathstr
 * starting at index @start and ending at index @stop (exclusive).
 *
 * Return: Pointer to the new buffer containing the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
	{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Find the command @cmd in the PATH string @pathstr.
 * @info: Pointer to the info struct.
 * @pathstr: The PATH string.
 * @cmd: The command to find.
 *
 * This function searches for the full path of the command
 * @cmd in the @pathstr
 *
 * Return: Pointer to the full path of the command if found,
 * or NULL otherwise.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
	{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
