#include "shell.h"

/**
 * main - entry point for shell app
 * @argc: argument count
 * @argv: argument vector
 *
 * Entry point to the shell program.
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_print_string(argv[0]);
				_print_string(": 0: Can't open ");
				_print_string(argv[1]);
				_print_char('\n');
				_print_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	main_shell_loop(info, argv);
	return (EXIT_SUCCESS);
}
