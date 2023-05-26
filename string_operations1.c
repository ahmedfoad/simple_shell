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
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
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
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
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
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
