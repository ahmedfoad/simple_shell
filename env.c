#include "shell.h"

/**
 * print_env_variables - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_env_variables(info_t *info)
{
	print_list_strings(info->env);
	return (0);
}

/**
 * get_env_value - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_env_value(info_t *info, const char *name)
{
	list_t *liststr = info->env;
	char *string;

	while (liststr)
	{
		string = is_prefix(liststr->str, name);
		if (string && *string)
		{
			return (string);
		}
		liststr = liststr->next;
	}
	return (NULL);
}

/**
 * set_env_variable - Initialize a new
 * environment variable,
 * or modify
 * existing one
 * @info: Structure containing
 * potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int set_env_variable(info_t *info)
{
	if (info->argc != 3)
	{
		_print_string("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing
 * potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_print_string("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
	{
		_unsetenv(info, info->argv[i]);
	}

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node_to_end(&node, environ[i], 0);
	}
	info->env = node;
	return (0);
}
