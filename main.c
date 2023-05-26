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
	info_t passinfos[] = { INFO_INIT };
	int fd1 = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd1)
		: "r" (fd1));

	if (argc == 2)
	{
		fd1 = open(argv[1], O_RDONLY);
		if (fd1 == -1)
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
		passinfos->readfd = fd1;
	}
	populate_env_list(passinfos);
	read_history(passinfos);
	main_shell_loop(passinfos, argv);
	return (EXIT_SUCCESS);
}
