#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: pointer to the parameter and return info struct
 *
 * Exits the shell with a given exit status.
 * Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		/* If there is an exit arguement */
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_print_string(info->argv[1]);
			_print_char('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @info: pointer to the parameter and return info struct
 *
 * Changes the current directory of the process.
 * Return: Always 0
 */
int change_directory(info_t *info)
{
	int chdir_ret;
	char *s, *dir, buffer[1024];

	s = getcwd(buffer, 1024);
	if (!s)
		print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env_value(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = get_env_value(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_compare(info->argv[1], "-") == 0)
	{
		if (!get_env_value(info, "OLDPWD="))
		{
			print_string(s);
			print_character('\n');
			return (1);
		}
		print_string(get_env_value(info, "OLDPWD=")), print_character('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_env_value(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_print_string(info->argv[1]), _print_char('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", get_env_value(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - displays help message
 * @info: pointer to the parameter and return info struct
 *
 * Displays help message.
 * Return: Always 0
 */
int display_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
		print_string(*arg_array); /* temp att_unused workaround */
	return (0);
}
