#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int i1 = 0;
	unsigned long int result1 = 0;

	if (*s == '+')
	{
		s++;
	}
	for (i1 = 0;  s[i1] != '\0'; i1++)
	{
		if (s[i1] >= '0' && s[i1] <= '9')
		{
			result1 *= 10;
			result1 += (s[i1] - '0');
			if (result1 > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (result1);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_print_string(info->fname);
	_print_string(": ");
	print_d(info->line_count, STDERR_FILENO);
	_print_string(": ");
	_print_string(info->argv[0]);
	_print_string(": ");
	_print_string(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = print_character;
	int i1, count1 = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	{
		__putchar = _print_char;
	}
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count1++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;
	for (i1 = 1000000000; i1 > 1; i1 /= 10)
	{
		if (_abs_ / i1)
		{
			__putchar('0' + current / i1);
			count1++;
		}
		current %= i1;
	}
	__putchar('0' + current);
	count1++;

	return (count1);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	char sign = 0;
	char *ptr1;
	static char *array1;
	static char text[50];
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array1 = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr1 = &text[49];
	*ptr1 = '\0';

	do	{
		*--ptr1 = array1[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
	{
		*--ptr1 = sign;
	}
	return (ptr1);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i1;

	for (i1 = 0; buf[i1] != '\0'; i1++)
	{
		if (buf[i1] == '#' && (!i1 || buf[i1 - 1] == ' '))
		{
			buf[i1] = '\0';
			break;
		}
	}
}
