#include "shell.h"

/**
 * string_copy - copies a string
 * @dest: pointer to destination
 * @src: pointer to source
 *
 * Copies the string from source to destination.
 * Return: pointer to destination
 */
char *string_copy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * string_duplicate - duplicates a string
 * @str: pointer to the string to duplicate
 *
 * Duplicates the given string.
 * Return: pointer to the duplicated string
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * print_string - prints a string
 * @str: pointer to the string
 *
 * Prints the given string to stdout.
 * Return: Nothing
 */
void print_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		print_character(str[i]);
		i++;
	}
}

/**
 * print_character - writes the character c to stdout
 * @c: The character to print
 *
 * Prints the given character to stdout.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_character(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
