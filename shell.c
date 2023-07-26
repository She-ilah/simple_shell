#include "shell.h"

/**
 * main_shell - Function is the main shell loop of the simple shell.
 * @check: parameter one.
 * @shargv: Argument vectors
 * Return: Returns 0 on success or 1 upon failure.
 */
int main_shell(info_t *check, char **shargv)
{
	ssize_t n = 0;
	int count = 0;

	while (n != -1 && count != -2)
	{
		init_info(check);
		if (shell_on(check))
			_puts("$ ");
		shell_putchar(BUF_FLUSH);
		n = get_input(check);
		if (n != -1)
		{
			shell_info(check, shargv);
			count = builtin_cmd(check);
			if (count == -1)
				find_cmd(check);
		}
		else if (shell_on(check))
			_putchar('\n');
		shell_free_info(check, 0);
	}
	shell_write_hist(check);
	shell_free_info(check, 1);
	if (!shell_on(check) && check->status)
		exit(check->status);
	if (count == -2)
	{
		if (check->err_num == -1)
			exit(check->status);
		exit(check->err_num);
	}
	return (count);
}

/**
 * builtin_cmd - Function identifies builtin commands.
 * @check: parameter one.
 * Return: 0 upon success, 1 upon failure or 2 if exited.
 */
int builtin_cmd(info_t *check)
{
	int i, count = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_set_env},
		{"unsetenv", shell_unset_env},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	/*Programming for builtin commands*/
	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(check->argv[0], builtintbl[i].type) == 0)
		{
			check->line_count++;
			count = builtintbl[i].func(check);
			break;
		}
	return (count);
}

/**
 * find_cmd - Function finds a specified command in PATH.
 * @check: parameter one.
 * Return: void
 */
void find_cmd(info_t *check)
{
	char *path = NULL;
	int i, k;

	check->path = check->argv[0];
	if (check->linecount_flag == 1)
	{
		check->line_count++;
		check->linecount_flag = 0;
	}
	for (i = 0, k = 0; check->arg[i]; i++)
		if (!char_split(check->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(check, shell_env_val(check, "PATH="), check->argv[0]);
	if (path)
	{
		check->path = path;
		fork_cmd(check);
	}
	else
	{
		if ((shell_on(check) || shell_env_val(check, "PATH=")
					|| check->argv[0][0] == '/') && is_cmd(check, check->argv[0]))
			fork_cmd(check);
		else if (*(check->arg) != '\n')
		{
			check->status = 127;
			shell_printf_err(check, "not found\n");
		}
	}
}

/**
 * fork_cmd - Function runs the cmd.
 * @check: parameter one.
 * Return: void
 */
void fork_cmd(info_t *check)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(check->path, check->argv, shell_ret_env(check)) == -1)
		{
			shell_free_info(check, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(check->status));
		if (WIFEXITED(check->status))
		{
			check->status = WEXITSTATUS(check->status);
			if (check->status == 126)
				shell_printf_err(check, "Permission denied\n");
		}
	}
}

