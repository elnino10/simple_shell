#include "main.h"

/**
 * clr_info - resets info_t struct
 * @info: struct address
 *
 * Return: nothing
 */
void clr_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - sets info_t struct
 * @info: struct info_t address
 * @argv: argument vector
 *
 * Return: nothing
 */
void set_info(info_t *info, char **argv)
{
	int index = 0;

	info->fname = argv[0];

	if (info->arg)
	{
		info->argv = _strtok_func(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (index = 0; info->argv && info->argv[index]; index++)
			;
		info->argc = index;

		/*repl_alias(info);*/
		/*repl_variable(info);*/
	}
}

/**
 * free_info - frees info_t struct
 * @info: address of info_t struct
 * @fields: true if all fields are freed
 */
void free_info(info_t *info, int fields)
{
	free_grid(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (fields)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list_t(&(info->env));
		if (info->history)
			free_list_t(&(info->history));
		if (info->alias)
			free_list_t(&(info->alias));
		free_grid(info->environ);
		info->environ = NULL;
		free_ptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}

/**
 * read_buffer - reads buffer
 * @info: parameter struct
 * @buffer: buffer
 * @size: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *size)
{
	ssize_t n_read = 0;

	if (*size)
		return (0);

	n_read = read(info->readfd, buffer, READ_BUFFER_SZ);
	if (n_read >= 0)
		*size = n_read;

	return (n_read);
}

