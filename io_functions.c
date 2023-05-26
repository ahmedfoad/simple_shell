#include "shell.h"

/**
 * _print_string - writes a string to stderr
 * @str: the string to be printed
 *
 * Prints a string of characters to stderr.
 * Return: Nothing.
 */
void _print_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_print_char(str[i]);
		i++;
	}
}

/**
 * _print_char - writes a character to stderr
 * @c: The character to print
 *
 * Writes a character to stderr.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print_char(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _write_to_fd - writes a character to a given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Writes a character to a given file descriptor.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _write_string_to_fd - writes a string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Writes a string of characters to a given file descriptor.
 * Return: The number of characters written.
 */
int _write_string_to_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _write_to_fd(*str++, fd);
	}
	return (i);
}
