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
	int i1 = 0;

	if (src == 0 || dest == src)
	{
		return (dest);
	}
	while (src[i1])
	{
		dest[i1] = src[i1];
		i1++;
	}
	dest[i1] = 0;
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
	int length1 = 0;
	char *ret1;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		length1++;
	}
	ret1 = malloc(sizeof(char) * (length1 + 1));
	if (!ret1)
	{
		return (NULL);
	}
	for (length1++; length1--;)
	{
		ret1[length1] = *--str;
	}
	return (ret1);
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
	int i1 = 0;

	if (!str)
	{
		return;
	}
	while (str[i1] != '\0')
	{
		print_character(str[i1]);
		i1++;
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
	static char buf[WRITE_BUF_SIZE];
	static int i1;


	if (c == BUF_FLUSH || i1 >= WRITE_BUF_SIZE)
	{
		write(1, buf, i1);
		i1 = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i1++] = c;
	}
	return (1);
}
