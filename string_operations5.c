#include "shell.h"

/**
 * get_string_length - returns the length of a string
 * @str: pointer to the string whose length to check
 *
 * Returns the length of the given string.
 * Return: integer length of string
 */
int get_string_length(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * string_compare - performs lexicographic comparison of two strings
 * @str1: pointer to the first string
 * @str2: pointer to the second string
 *
 * Performs lexicographic comparison of two strings.
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * is_prefix - checks if needle is a prefix of haystack
 * @haystack: pointer to the string to search
 * @needle: pointer to the substring to find
 *
 * Checks if needle is a prefix of haystack.
 * Return: address of next char of haystack or NULL
 */
char *is_prefix(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * string_concatenate - concatenates two strings
 * @dest: pointer to the destination buffer
 * @src: pointer to the source buffer
 *
 * Concatenates the given source string to the destination string.
 * Return: pointer to destination buffer
 */
char *string_concatenate(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
