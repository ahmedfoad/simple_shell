#include "shell.h"

/**
 * is_executable_command - determines
 * if a file is an executable command
 * @info: pointer to shell's information struct
 * @path: path to the file
 *
 * Determines if a file is an executable command.
 * Return: 1 if true, 0 otherwise
 */
int is_executable_command(info_t *info, char *path)
{
	struct stat stat1;

	(void)info;
	if (!path || stat(path, &stat1))
	{
		return (0);
	}

	if (stat1.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Duplicates characters from a string.
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char text[1024];
	int i1 = 0, i = 0;

	for (i = 0, i1 = start; i1 < stop; i1++)
	{
		if (pathstr[i1] != ':')
		{
			text[i++] = pathstr[i1];
		}
	}
	text[i] = 0;
	return (text);
}

/**
 * find_command_path - finds this cmd in the PATH string
 * @info: pointer to shell's information struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Finds the full path of a command in the PATH string.
 * Return: full path of cmd if found or NULL
 */
char *find_command_path(info_t *info, char *pathstr, char *cmd)
{
	char *c;
	int i1 = 0, pos = 0;


	if (!pathstr)
		return (NULL);
	if ((get_string_length(cmd) > 2) && is_prefix(cmd, "./"))
	{
		if (is_executable_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i1] || pathstr[i1] == ':')
		{
			c = duplicate_chars(pathstr, pos, i1);
			if (!*c)
				string_concatenate(c, cmd);
			else
			{
				string_concatenate(c, "/");
				string_concatenate(c, cmd);
			}
			if (is_executable_command(info, c))
				return (c);
			if (!pathstr[i1])
				break;
			pos = i1;
		}
		i1++;
	}
	return (NULL);
}
