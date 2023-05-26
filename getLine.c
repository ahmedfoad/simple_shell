#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t ssize = 0;
	size_t size = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*free_and_null_ptr((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
		#else
		ssize = _getline(info, buf, &size);
		#endif
		if (ssize > 0)
		{
			if ((*buf)[ssize - 1] == '\n')
			{
				(*buf)[ssize - 1] = '\0'; /* remove trailing newline */
				ssize--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_find_character(*buf, ';')) is this a command chain? */
			{
				*len = ssize;
				info->cmd_buf = buf;
			}
		}
	}
	return (ssize);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf1; /* the ';' command chain buffer */
	static size_t size, size2, size1;
	ssize_t ssize = 0;
	char **buf_p = &(info->arg), *p;

	print_character(BUF_FLUSH);
	ssize = input_buf(info, &buf1, &size1);
	if (ssize == -1) /* EOF */
		return (-1);
	if (size1)	/* we have commands left in the chain buffer */
	{
		size2 = size; /* init new iterator to current buf position */
		p = buf1 + size; /* get pointer for return */

		check_should_chain(info, buf1, &size2, size, size1);
		while (size2 < size1) /* iterate to semicolon or end */
		{
			if (is_chain_delimiter(info, buf1, &size2))
			{
				break;
			}
			size2++;
		}

		size = size2 + 1; /* increment past nulled ';'' */
		if (size >= size1) /* reached end of buffer? */
		{
			size = size1 = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (get_string_length(p)); /* return length of current command */
	}

	*buf_p = buf1; /* else not a chain, pass back buffer from _getline() */
	return (ssize); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t ssize = 0;

	if (*i)
	{
		return (0);
	}
	ssize = read(info->readfd, buf, READ_BUF_SIZE);
	if (ssize >= 0)
	{
		*i = ssize;
	}
	return (ssize);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	size_t size2;
	ssize_t ssize = 0, ssize1 = 0;
	static char text[READ_BUF_SIZE];
	static size_t size, size1;

	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		ssize1 = *length;
	if (size == size1)
		size = size1 = 0;

	ssize = read_buf(info, text, &size1);
	if (ssize == -1 || (ssize == 0 && size1 == 0))
		return (-1);

	c = _find_character(text + size, '\n');
	size2 = c ? 1 + (unsigned int)(c - text) : size1;
	new_p = custom_realloc(p, ssize1, ssize1 ? ssize1 + size2 : size2 + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (ssize1)
		_concatenate_strings(new_p, text + size, size2 - size);
	else
		_copy_string(new_p, text + size, size2 - size + 1);

	ssize1 += size2 - size;
	size = size2;
	p = new_p;

	if (length)
	{
		*length = ssize1;
	}
	*ptr = p;
	return (ssize1);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	print_string("\n");
	print_string("$ ");
	print_character(BUF_FLUSH);
}
