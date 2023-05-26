#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_string_array(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *liststr = info->env;
	size_t index = 0;
	char *string;

	if (!liststr || !var)
	{
		return (0);
	}

	while (liststr)
	{
		string = is_prefix(liststr->str, var);
		if (string && *string == '=')
		{
			info->env_changed = delete_node_by_index(&(info->env), index);
			index = 0;
			liststr = info->env;
			continue;
		}
		liststr = liststr->next;
		index++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *block = NULL;
	list_t *liststr;
	char *string;

	if (!var || !value)
	{
		return (0);
	}

	block = malloc(get_string_length(var) + get_string_length(value) + 2);
	if (!block)
	{
		return (1);
	}
	string_copy(block, var);
	string_concatenate(block, "=");
	string_concatenate(block, value);
	liststr = info->env;
	while (liststr)
	{
		string = is_prefix(liststr->str, var);
		if (string && *string == '=')
		{
			free(liststr->str);
			liststr->str = block;
			info->env_changed = 1;
			return (0);
		}
		liststr = liststr->next;
	}
	add_node_to_end(&(info->env), block, 0);
	free(block);
	info->env_changed = 1;
	return (0);
}
