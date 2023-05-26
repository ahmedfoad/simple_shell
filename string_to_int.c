#include "shell.h"

/**
 * is_interactive - checks if shell is in interactive mode
 * @info: struct address
 *
 * Return: true if interactive mode, false otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: true if character is delimiter, false otherwise
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 *is_alpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * string_to_int - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */

int string_to_int(char *s)
{
	int i1, sign1 = 1, flag1 = 0, output1;
	unsigned int result = 0;

	for (i1 = 0;  s[i1] != '\0' && flag1 != 2; i1++)
	{
		if (s[i1] == '-')
		{
			sign1 *= -1;
		}

		if (s[i1] >= '0' && s[i1] <= '9')
		{
			flag1 = 1;
			result *= 10;
			result += (s[i1] - '0');
		}
		else if (flag1 == 1)
		{
			flag1 = 2;
		}
	}

	if (sign1 == -1)
	{
		output1 = -result;
	}
	else
	{
		output1 = result;
	}

	return (output1);
}
