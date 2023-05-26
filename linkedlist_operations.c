#include "shell.h"

/**
 * list_length - determines length of linked list
 * @head: pointer to first node
 *
 * Determines the length of a linked list.
 * Return: size of list
 */
size_t list_length(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_to_string_array - returns an array
 * of strings of the list->str
 * @head: pointer to first node
 *
 * Converts a linked list to an array of strings.
 * Return: array of strings
 */
char **list_to_string_array(list_t *head)
{
	list_t *node = head;
	size_t i = list_length(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(get_string_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = string_copy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_linked_list - prints all
 * elements of a list_t linked list
 * @h: pointer to first node
 *
 * Prints all elements of a linked list.
 * Return: size of list
 */
size_t print_linked_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(convert_number(h->num, 10, 0));
		print_character(':');
		print_character(' ');
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * find_node_with_prefix - returns node
 * whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Returns the node whose string starts
 * with a given prefix and next character.
 * Return: match node or null
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = is_prefix(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the
 * index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Gets the index of a node in a linked list.
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
