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
	int exitcheck1;

	if (info->argv[1])
	{
		/* If there is an exit arguement */
		exitcheck1 = _erratoi(info->argv[1]);
		if (exitcheck1 == -1)
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
	int ret;
	char *text, *dir, buffer[1024];

	text = getcwd(buffer, 1024);
	if (!text)
		print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env_value(info, "HOME=");
		if (!dir)
			ret = chdir((dir = get_env_value(info, "PWD=")) ? dir : "/");
		else
			ret = chdir(dir);
	}
	else if (string_compare(info->argv[1], "-") == 0)
	{
		if (!get_env_value(info, "OLDPWD="))
		{
			print_string(text);
			print_character('\n');
			return (1);
		}
		print_string(get_env_value(info, "OLDPWD=")), print_character('\n');
		ret = chdir((dir = get_env_value(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		ret = chdir(info->argv[1]);
	}
	if (ret == -1)
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
	char **array;

	array = info->argv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
	{
		print_string(*array);
	}
	return (0);
}
