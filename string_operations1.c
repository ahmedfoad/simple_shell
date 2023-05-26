#include "shell.h"

/**
 * _copy_string - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 *
 * Copies @n characters from @src to @dest.
 * Return: A pointer to the destination string.
 */
char *_copy_string(char *dest, char *src, int n)
{
	int i1, i;
	char *str = dest;

	i1 = 0;
	while (src[i1] != '\0' && i1 < n - 1)
	{
		dest[i1] = src[i1];
		i1++;
	}
	if (i1 < n)
	{
		i = i1;
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (str);
}

/**
 * _concatenate_strings - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the maximum number of bytes to be used from @src
 *
 * Concatenates @src to the end of @dest, using at most @n bytes.
 * Return: A pointer to the resulting string.
 */
char *_concatenate_strings(char *dest, char *src, int n)
{
	int i1, i;
	char *s = dest;

	i1 = 0;
	i = 0;
	while (dest[i1] != '\0')
	{
		i1++;
	}
	while (src[i] != '\0' && i < n)
	{
		dest[i1] = src[i];
		i1++;
		i++;
	}
	if (i < n)
	{
		dest[i1] = '\0';
	}
	return (s);
}

/**
 * _find_character - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 *
 * Locates the first occurrence of @c in @s.
 * Return: A pointer to the memory area of @s that contains @c.
 */
char *_find_character(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}
