#include "shell.h"

/**
 * shell_exit - Function exits the simple shell
 * @check: Parameter one.
 * Return: exit and gives an exit message.
 */
int shell_exit(info_t *check)
{
	int exitcheck;

	if (check->argv[1])
	{
		exitcheck = str_to_int(check->argv[1]);
		if (exitcheck == -1)
		{
			check->status = 2;
			shell_printf_err(check, "Unidentified Number: ");
			shell_puts(check->argv[1]);
			shell_putchar('\n');
			return (1);
		}
		check->err_num = str_to_int(check->argv[1]);
		return (-2);
	}
	check->err_num = -1;
	return (-2);
}

/**
 * shell_cd - Function changes between directories.
 * @check: Parameter one.
 * Return: Function returns 0.
 */
int shell_cd(info_t *check)
{
	char *str, *curr_dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("Failed to get the cwd \n");
	if (!check->argv[1])
	{
		curr_dir = shell_env_val(check, "HOME=");
		if (!curr_dir)
			chdir_ret =
				chdir((curr_dir = shell_env_val(check, "PWD=")) ? curr_dir : "/");
		else
			chdir_ret = chdir(curr_dir);
	}
	else if (_strcmp(check->argv[1], "-") == 0)
	{
		if (!shell_env_val(check, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(shell_env_val(check, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((curr_dir = shell_env_val(check, "OLDPWD=")) ? curr_dir : "/");
	}
	else
		chdir_ret = chdir(check->argv[1]);
	if (chdir_ret == -1)
	{
		shell_printf_err(check, "unable to cd to ");
		shell_puts(check->argv[1]), shell_putchar('\n');
	}
	else
	{
		shell_init_env(check, "OLDPWD", shell_env_val(check, "PWD="));
		shell_init_env(check, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shell_help - Function changes the current directory.
 * @check: Prototype one
 * Return: Function returns 0
 */
int shell_help(info_t *check)
{
	char **arr;

	arr = check->argv;
	_puts("Help call has been successful \n");
	if (0)
		_puts(*arr);
	return (0);
}
