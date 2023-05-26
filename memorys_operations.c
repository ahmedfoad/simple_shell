#include "shell.h"

/**
 * custom_memset - fills memory with a constant byte
 * @s: pointer to the memory area
 * @byte: the byte to fill *s with
 * @n: the number of bytes to be filled
 *
 * Fills memory with a constant byte.
 * Return: (s) a pointer to the memory area s
 */
char *custom_memset(char *s, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = byte;
	return (s);
}

/**
 * free_string_array - frees a string of strings
 * @str_arr: string of strings to be freed
 *
 * Frees a string of strings.
 * Return: void
 */
void free_string_array(char **str_arr)
{
	char **a = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
		free(*str_arr++);
	free(a);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to previously allocated block of memory
 * @old_size: size of previously allocated block
 * @new_size: size of new memory block to be allocated
 *
 * Reallocates a block of memory.
 * Return: pointer to the previous block.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * free_and_null_ptr - frees a pointer
 * and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Frees a pointer and
 * sets its address to NULL.
 * Return: 1 if freed, otherwise 0.
 */
int free_and_null_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
