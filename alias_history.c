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
	int ret1;
	char *string, c1;


	string = _find_character(str, '=');
	if (!string)
	{
		return (1);
	}
	c1 = *string;
	*string = 0;
	ret1 = delete_node_by_index(&(info->alias),
		get_node_index(info->alias, find_node_with_prefix(info->alias, str, -1)));
	*string = c1;
	return (ret1);
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
	char *text;

	text = _find_character(str, '=');
	if (!text)
	{
		return (1);
	}
	if (!*++text)
	{
		return (unset_alias_from_string(info, str));
	}

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
	char *text = NULL, *string = NULL;

	if (node)
	{
		text = _find_character(node->str, '=');
		for (string = node->str; string <= text; string++)
		{
			print_character(*string);
		}
		print_character('\'');
		print_string(text + 1);
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
	int i1 = 0;
	char *string = NULL;
	list_t *liststr = NULL;

	if (info->argc == 1)
	{
		liststr = info->alias;
		while (liststr)
		{
			print_alias_string(liststr);
			liststr = liststr->next;
		}
		return (0);
	}
	for (i1 = 1; info->argv[i1]; i1++)
	{
		string = _find_character(info->argv[i1], '=');
		if (string)
		{
			set_alias_from_string(info, info->argv[i1]);
		}
		else
		{
			print_alias_string(find_node_with_prefix(info->alias, info->argv[i1], '='));
		}
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
