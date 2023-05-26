#include "shell.h"

/**
 * unset_alias_from_string - removes an alias string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias_from_string(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _find_character(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_by_index(&(info->alias),
		get_node_index(info->alias, find_node_with_prefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias_from_string - sets alias
 * to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias_from_string(info_t *info, char *str)
{
	char *p;

	p = _find_character(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_from_string(info, str));

	unset_alias_from_string(info, str);
	return (add_node_to_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias_string - prints an
 * alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_string(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _find_character(node->str, '=');
		for (a = node->str; a <= p; a++)
			print_character(*a);
		print_character('\'');
		print_string(p + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * handle_alias_builtin - mimics the
 * alias builtin (man alias)
 * @info: Structure containing
 * potential
 * arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int handle_alias_builtin(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias_string(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _find_character(info->argv[i], '=');
		if (p)
			set_alias_from_string(info, info->argv[i]);
		else
			print_alias_string(find_node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}

/**
 * display_history - displays the history list,
 * one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing
 * potential arguments.
 * Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
	print_linked_list(info->history);
	return (0);
}
