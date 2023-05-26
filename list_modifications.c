#include "shell.h"

/**
 * add_node_to_start - adds a node
 * to the start of the list
 * @head: address of
 * pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Adds a node to the beginning of a linked list.
 * Return: pointer to new head of list
 */
list_t *add_node_to_start(list_t **head, const char *str, int num)
{
	list_t *block;

	if (!head)
	{
		return (NULL);
	}
	block = malloc(sizeof(list_t));
	if (!block)
	{
		return (NULL);
	}
	custom_memset((void *)block, 0, sizeof(list_t));
	block->num = num;
	if (str)
	{
		block->str = string_duplicate(str);
		if (!block->str)
		{
			free(block);
			return (NULL);
		}
	}
	block->next = *head;
	*head = block;
	return (block);
}

/**
 * add_node_to_end - adds a
 * node to the end of the list
 * @head: address of
 * pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Adds a node to the end of a linked list.
 * Return: pointer to new node
 */
list_t *add_node_to_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
	{
		return (NULL);
	}

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}
	custom_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = string_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * print_list_strings - prints only
 * the str element of a
 * list_t linked list
 * @h: pointer to first node
 *
 * Prints only the `str` element
 * of a linked list.
 * Return: size of list
 */
size_t print_list_strings(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_by_index - deletes
 * node at given index
 * @head: address of
 * pointer to first node
 * @index: index of node to delete
 *
 * Deletes a node at a given
 * index in a linked list.
 * Return: 1 on success, 0 on failure
 */
int delete_node_by_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
	{
		return (0);
	}

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_linked_list - frees all
 * nodes of a list
 * @head_ptr: address of
 * pointer to head node
 *
 * Frees all nodes of a linked list.
 * Return: void
 */
void free_linked_list(list_t **head_ptr)
{
	list_t *list, *next_list, *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}
	head = *head_ptr;
	list = head;
	while (list)
	{
		next_list = list->next;
		free(list->str);
		free(list);
		list = next_list;
	}
	*head_ptr = NULL;
}
