#include "shell.h"

/**
 * split_string_into_words - splits a string
 * into words, ignoring repeat delimiters
 * @str: the input string
 * @delim: the delimiter string
 *
 * Splits a string into words, ignoring repeat delimiters.
 * Return: a pointer to an array of strings, or NULL on failure.
 */
char **split_string_into_words(char *str, char *delim)
{
	int i1, i, k1, m1, numofwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i1 = 0; str[i1] != '\0'; i1++)
		if (!is_delimiter(str[i1], delim) &&
			(is_delimiter(str[i1 + 1], delim) || !str[i1 + 1]))
		{
			numofwords++;
		}

	if (numofwords == 0)
		return (NULL);
	s = malloc((1 + numofwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i1 = 0, i = 0; i < numofwords; i++)
	{
		while (is_delimiter(str[i1], delim))
			i1++;
		k1 = 0;
		while (!is_delimiter(str[i1 + k1], delim) && str[i1 + k1])
			k1++;
		s[i] = malloc((k1 + 1) * sizeof(char));
		if (!s[i])
		{
			for (k1 = 0; k1 < i; k1++)
				free(s[k1]);
			free(s);
			return (NULL);
		}
		for (m1 = 0; m1 < k1; m1++)
			s[i][m1] = str[i1++];
		s[i][m1] = 0;
	}
	s[i] = NULL;
	return (s);
}

/**
 * split_string_into_words_2 - splits a string into words
 * @str: the input string
 * @delim: the delimiter
 *
 * Splits a string into words.
 * Return: a pointer to an array of strings, or NULL on failure.
 */
char **split_string_into_words_2(char *str, char delim)
{
	int i1, i, k1, m1, numofwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i1 = 0; str[i1] != '\0'; i1++)
	{
		if ((str[i1] != delim && str[i1 + 1] == delim) ||
			(str[i1] != delim && !str[i1 + 1]) || str[i1 + 1] == delim)
			numofwords++;
	}
	if (numofwords == 0)
		return (NULL);
	s = malloc((1 + numofwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i1 = 0, i = 0; i < numofwords; i++)
	{
		while (str[i1] == delim && str[i1] != delim)
			i1++;
		k1 = 0;
		while (str[i1 + k1] != delim && str[i1 + k1] && str[i1 + k1] != delim)
		{
			k1++;
		}
		s[i] = malloc((k1 + 1) * sizeof(char));
		if (!s[i])
		{
			for (k1 = 0; k1 < i; k1++)
				free(s[k1]);
			free(s);
			return (NULL);
		}
		for (m1 = 0; m1 < k1; m1++)
			s[i][m1] = str[i1++];
		s[i][m1] = 0;
	}
	s[i] = NULL;
	return (s);
}
