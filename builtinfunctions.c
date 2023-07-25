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
		exitcheck = _erratoi(check->argv[1]);
		if (exitcheck == -1)
		{
			check->status = 2;
			print_error(check, "Unidentified Number: ");
			_eputs(check->argv[1]);
			_eputchar('\n');
			return (1);
		}
		check->err_num = _erratoi(check->argv[1]);
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
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!check->argv[1])
	{
		curr_dir = _getenv(check, "HOME=");
		if (!curr_dir)
			chdir_ret =
				chdir((curr_dir = _getenv(check, "PWD=")) ? curr_dir : "/");
		else
			chdir_ret = chdir(curr_dir);
	}
	else if (_strcmp(check->argv[1], "-") == 0)
	{
		if (!_getenv(check, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(check, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((curr_dir = _getenv(check, "OLDPWD=")) ? curr_dir : "/");
	}
	else
		chdir_ret = chdir(check->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(check, "can't cd to ");
		_eputs(check->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(check, "OLDPWD", _getenv(check, "PWD="));
		_setenv(check, "PWD", getcwd(buffer, 1024));
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
	_puts("The help call works \n");
	if (0)
		_puts(*arr);
	return (0);
}

