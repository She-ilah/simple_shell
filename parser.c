#include "shell.h"

/**
 * is_cmd - Check if a file is an executable command.
 * @check: Pointer to the info struct.
 * @path: Path to the file.
 *
 * This function determines whether the given file at
 * the specified path is an
 * executable command.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *check, char *path)
{
	struct stat st;
	(void)check;
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
 * @mainstr: The PATH string.
 * @st_index: Starting index.
 * @stop: Stopping index (exclusive).
 *
 * This function creates a new buffer containing
 * the characters from @pathstr
 * starting at index @start and ending at index @stop (exclusive).
 *
 * Return: Pointer to the new buffer containing the duplicated characters.
 */
char *dup_chars(char *mainstr, int st_index, int stop)
	{
	static char buffer[1024];
	int n = 0, a = 0;

	for (a = 0, n = st_index; n < stop; n++)
		if (mainstr[n] != ':')
			buffer[a++] = mainstr[n];
	buffer[a] = 0;
	return (buffer);
}

/**
 * find_path - Find the command @cmd in the PATH string @pathstr.
 * @check: Pointer to the info struct.
 * @mainstr: The PATH string.
 * @cmd: The command to find.
 *
 * This function searches for the full path of the command
 * @cmd in the @pathstr
 *
 * Return: Pointer to the full path of the command if found,
 * or NULL otherwise.
 */
char *find_path(info_t *check, char *mainstr, char *cmd)
	{
	int n = 0, place = 0;
	char *path;

	if (!mainstr)
		return (NULL);
	if ((strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(check, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!mainstr[n] || mainstr[n] == ':')
		{
			path = dup_chars(mainstr, place, n);
			if (!*path)
				strcat(path, cmd);
			else
			{
				strcat(path, "/");
				strcat(path, cmd);
			}
			if (is_cmd(check, path))
				return (path);
			if (!mainstr[n])
				break;
			place = n;
		}
		n++;
	}
	return (NULL);
	}
