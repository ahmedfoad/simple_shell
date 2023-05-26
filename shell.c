#include "shell.h"

/**
 * main_shell_loop - main shell loop
 * @info: pointer to the parameter and return info struct
 * @av: pointer to the argument vector from main()
 *
 * Main shell loop that reads input, parses input,
 * finds the corresponding command to execute, and executes the command.
 * Return: 0 on success, 1 on error, or error code
 */
int main_shell_loop(info_t *info, char **av)
{
	ssize_t ssize = 0;
	int ret = 0;

	while (ssize != -1 && ret != -2)
	{
		clear_info(info);
		if (is_interactive(info))
		{
			print_string("$ ");
		}
		_print_char(BUF_FLUSH);
		ssize = get_input(info);
		if (ssize != -1)
		{
			set_info(info, av);
			ret = find_builtin_command(info);
			if (ret == -1)
			{
				find_command(info);
			}
		}
		else if (is_interactive(info))
		{
			print_character('\n');
		}
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!is_interactive(info) && info->status)
	{
		exit(info->status);
	}
	if (ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (ret);
}

/**
 * find_builtin_command - finds a builtin command
 * @info: pointer to the parameter and return info struct
 *
 * Finds the corresponding builtin command to execute.
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_command(info_t *info)
{
	int i1, ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", print_env_variables},
		{"help", display_help},
		{"history", display_history},
		{"setenv", set_env_variable},
		{"unsetenv", _myunsetenv},
		{"cd", change_directory},
		{"alias", handle_alias_builtin},
		{NULL, NULL}
	};

	for (i1 = 0; builtintbl[i1].type; i1++)
		if (string_compare(info->argv[0], builtintbl[i1].type) == 0)
		{
			info->line_count++;
			ret = builtintbl[i1].func(info);
			break;
		}
	return (ret);
}

/**
 * find_command - finds a command in PATH
 * @info: pointer to the parameter and return info struct
 *
 * Finds the corresponding command in PATH to execute.
 * Return: void
 */
void find_command(info_t *info)
{
	char *path1 = NULL;
	int i1, i;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i1 = 0, i = 0; info->arg[i1]; i1++)
	{
		if (!is_delimiter(info->arg[i1], " \t\n"))
		{
			i++;
		}
	}
	if (!i)
	{
		return;
	}

	path1 = find_command_path(info, get_env_value(info, "PATH="), info->argv[0]);
	if (path1)
	{
		info->path = path1;
		fork_command(info);
	}
	else
	{
		if ((is_interactive(info) || get_env_value(info, "PATH=")
			|| info->argv[0][0] == '/') && is_executable_command(info, info->argv[0]))
		{
			fork_command(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - forks a new process to run the command
 * @info: pointer to the parameter and return info struct
 *
 * Forks a new process to execute the corresponding command.
 * Return: void
 */
void fork_command(info_t *info)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
			{
				print_error(info, "Permission denied\n");
			}
		}
	}
}
