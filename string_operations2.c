#include "shell.h"

/**
 * is_chain_delimiter - checks if
 * current character in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Checks if the current character
 * in @buf is a chain delimiter.
 * If yes, updates @info with
 * the appropriate command buffer type.
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain_delimiter(info_t *info, char *buf, size_t *p)
{
	size_t size = *p;

	if (buf[size] == '&' && buf[size + 1] == '&')
	{
		buf[size] = 0;
		size++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[size] == '|' && buf[size + 1] == '|')
	{
		buf[size] = 0;
		size++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[size] == ';') /* found end of this command */
	{
		buf[size] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = size;
	return (1);
}

/**
 * check_should_chain - checks if we
 * should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Checks if we should continue chaining based on the last command's status.
 * If yes, updates @buf and @p accordingly.
 * Return: Void.
 */
void check_should_chain(info_t *info,
	char *buf,
	size_t *p,
	size_t i,
	size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces
 * an alias in the tokenized string
 * @info: the parameter struct
 *
 * Replaces an alias in
 * the tokenized string with its corresponding value.
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_node_with_prefix(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		p = _find_character(node->str, '=');
		if (!p)
		{
			return (0);
		}
		p = string_duplicate(p + 1);
		if (!p)
		{
			return (0);
		}
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces
 * variables in the tokenized string
 * @info: the parameter struct
 *
 * Replaces variables in
 * the tokenized string with their corresponding values.
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i1 = 0;
	list_t *liststr;

	for (i1 = 0; info->argv[i1]; i1++)
	{
		if (info->argv[i1][0] != '$' || !info->argv[i1][1])
			continue;

		if (!string_compare(info->argv[i1], "$?"))
		{
			_string_replace(&(info->argv[i1]),
				string_duplicate(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!string_compare(info->argv[i1], "$$"))
		{
			_string_replace(&(info->argv[i1]),
				string_duplicate(convert_number(getpid(), 10, 0)));
			continue;
		}
		liststr = find_node_with_prefix(info->env, &info->argv[i1][1], '=');
		if (liststr)
		{
			_string_replace(&(info->argv[i1]),
				string_duplicate(_find_character(liststr->str, '=') + 1));
			continue;
		}
		_string_replace(&info->argv[i1], string_duplicate(""));

	}
	return (0);
}

/**
 * _string_replace - replaces a string
 * @old: address of old string
 * @new: new string
 *
 * Replaces a string with a new one.
 * Return: 1 if replaced, 0 otherwise.
 */
int _string_replace(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
