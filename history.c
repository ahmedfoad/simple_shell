#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf1, *dir1;

	dir1 = get_env_value(info, "HOME=");
	if (!dir1)
	{
		return (NULL);
	}
	buf1 = malloc(sizeof(char) * (get_string_length(dir1)
			+ get_string_length(HIST_FILE) + 2));
	if (!buf1)
	{
		return (NULL);
	}
	buf1[0] = 0;
	string_copy(buf1, dir1);
	string_concatenate(buf1, "/");
	string_concatenate(buf1, HIST_FILE);
	return (buf1);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t ssize;
	char *block = get_history_file(info);
	list_t *liststr = NULL;

	if (!block)
	{
		return (-1);
	}

	ssize = open(block, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(block);
	if (ssize == -1)
	{
		return (-1);
	}
	for (liststr = info->history; liststr; liststr = liststr->next)
	{
		_write_string_to_fd(liststr->str, ssize);
		_write_to_fd('\n', ssize);
	}
	_write_to_fd(BUF_FLUSH, ssize);
	close(ssize);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	ssize_t file_handle, ssize, ssize1 = 0;
	struct stat st;
	int i1, last1 = 0, linecount1 = 0;
	char *block = NULL, *block1 = get_history_file(info);

	if (!block1)
		return (0);

	file_handle = open(block1, O_RDONLY);
	free(block1);
	if (file_handle == -1)
		return (0);
	if (!fstat(file_handle, &st))
		ssize1 = st.st_size;
	if (ssize1 < 2)
		return (0);
	block = malloc(sizeof(char) * (ssize1 + 1));
	if (!block)

		return (0);
	ssize = read(file_handle, block, ssize1);
	block[ssize1] = 0;
	if (ssize <= 0)
		return (free(block), 0);
	close(file_handle);
	for (i1 = 0; i1 < ssize1; i1++)
		if (block[i1] == '\n')
		{
			block[i1] = 0;
			build_history_list(info, block + last1, linecount1++);
			last1 = i1 + 1;
		}
	if (last1 != i1)
		build_history_list(info, block + last1, linecount1++);
	free(block);
	info->histcount = linecount1;
	while (info->histcount-- >= HIST_MAX)
		delete_node_by_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *liststr = NULL;

	if (info->history)
	{
		liststr = info->history;
	}
	add_node_to_end(&liststr, buf, linecount);

	if (!info->history)
	{
		info->history = liststr;
	}
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *liststr = info->history;
	int i1 = 0;

	while (liststr)
	{
		liststr->num = i1++;
		liststr = liststr->next;
	}
	return (info->histcount = i1);
}
