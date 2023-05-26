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
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
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
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
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
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((get_string_length(cmd) > 2) && is_prefix(cmd, "./"))
	{
		if (is_executable_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				string_concatenate(path, cmd);
			else
			{
				string_concatenate(path, "/");
				string_concatenate(path, cmd);
			}
			if (is_executable_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
