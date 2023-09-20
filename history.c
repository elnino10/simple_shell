#include "main.h"

/**
 * rd_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rd_history(info_t *info)
{
	int line_count = 0, last = 0, i;
	ssize_t fd, readlen, filesize = 0;
	char *filename = get_history(info), *buff = NULL;
	struct stat st_t;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st_t))
		filesize = st_t.st_size;
	if (filesize < 2)
		return (0);
	buff = malloc(sizeof(char) * (filesize + 1));
	if (!buff)
		return (0);
	readlen = read(fd, buff, filesize);
	buff[filesize] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < filesize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history(info, buff + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_history(info, buff + last, line_count++);
	free(buff);
	info->histcount = line_count;
	while (info->histcount-- >= MAX_HISTORY)
		del_node_at_index(&(info->history), 0);
	renum_history(info);
	return (info->histcount);
}

/**
 * get_history - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * build_history - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_history(info_t *info)
{
	list_t *node = info->history;
	int i;

	i = 0;
	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}

/**
 * wrt_history - creates and writes to file, or appends to existing file
 * @info: parameter struct
 *
 * Return: 1 when successful, and -1 otherwise
 */
int wrt_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->dir, fd);
		_putcharfd('\n', fd);
	}
	_putcharfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}
