#include "main.h"

/**
 * input_buffer - buffers commands
 * @info: parameter struct
 * @buff: address of buffer
 * @length: address of length
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buff, size_t *length)
{
	size_t len_p = 0;
	ssize_t n_read = 0;

	if (!*length)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		n_read = getline(buff, &len_p, stdin);
#else
		n_read = getline_func(info, buff, &len_p);
#endif
		if (n_read > 0)
		{
			if ((*buff)[n_read - 1] == '\n')
			{
				/* remove trailing newline */
				(*buff)[n_read - 1] = '\0';
				n_read--;
			}
			info->linecount_flag = 1;
			build_history(info, *buff, info->histcount++);
			/*remove_comments(*buff);*/

			if (_strchr(*buff, ';'))
			{
				*length = n_read;
				info->cmd_buf = buff;
			}
		}
	}
	return (n_read);
}

/**
 * user_input - gets an input line without newline
 * @info: parameter struct
 *
 * Return: number of bytes read
 */
ssize_t user_input(info_t *info)
{
	static char *buff; /*stores the command ';'*/
	char **buff_position = &(info->arg), *p;
	ssize_t n_read = 0;
	static size_t i, j, length;

	_putchar(BUFFER_FLUSH);
	n_read = input_buffer(info, &buff, &length);
	if (n_read == -1) /*EOF*/
		return (-1);
	if (length)
	{
		j = i; /* initialize iterator to current buff position */
		p = buff + i;
		check_list_chain(info, buff, &j, i, length);
		while (j < length)
		{
			if (is_list_chain(info, buff, &j))
				break;
			j++;
		}
		/*increment past nulled ';''*/
		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmd_buff_type = NORM_CMD;
		}
		*buff_position = p;
		return (_strlen(p));
	}
	*buff_position = buff;
	return (n_read);
}

/**
 * is_command - checks if file is an executable command
 * @info: info struct
 * @file_path: path to file
 *
 * Return: 1 if true or 0 otherwise
 */
int is_command(info_t *info, char *file_path)
{
	struct stat st_t;

	(void)info;
	if (!file_path || stat(file_path, &st_t))
		return (0);

	if (st_t.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
 * sigint_handler - ctrl-C blocker
 * @signal_num: signal number
 *
 * Return: void
 */
void sigint_handler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

/**
 * getline_func - gets line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @size: preallocated ptr buffer size, if it is not NULL
 *
 * Return: number of bytes read
 */
int getline_func(info_t *info, char **ptr, size_t *size)
{
	ssize_t n_read = 0, sz = 0;
	size_t k;
	static char buffer[READ_BUFFER_SZ];
	static size_t length, i;
	char *p = NULL, *ch, *p_cpy = NULL;

	p = *ptr;
	if (p && size)
		sz = *size;
	if (i == length)
		i = length = 0;
	n_read = read_buffer(info, buffer, &length);
	if (n_read == -1 || (n_read == 0 && length == 0))
		return (-1);

	ch = _strchr(buffer + i, '\n');
	k = ch ? 1 + (unsigned int)(ch - buffer) : length;
	p_cpy = __realloc(p, sz, sz ? sz + k : k + 1);
	if (!p_cpy)
		return (p ? free(p), -1 : -1);

	if (sz)
		_strncat(p_cpy, buffer + i, k - i);
	else
		_strncpy(p_cpy, buffer + i, k - i + 1);

	sz += k - i;
	i = k;
	p = p_cpy;

	if (size)
		*size = sz;
	*ptr = p;

	return (sz);
}

