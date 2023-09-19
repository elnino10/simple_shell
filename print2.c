#include "main.h"

/**
 * print_dec - prints decimal number
 * @ip: input
 * @fd: file-descriptor
 *
 * Return: number of printed characters
 */
int print_dec(int ip, int fd)
{
	int i, count = 0;
	unsigned int current, _absolute;
	int (*_err_putchar)(char) = _putchar;

	if (fd == STDERR_FILENO)
		_err_putchar = err_putchar;

	if (ip < 0)
	{
		_absolute = -ip;
		_err_putchar('-');
		count++;
	}
	else
		_absolute = ip;

	current = _absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_absolute / i)
		{
			_err_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	_err_putchar('0' + current);
	count++;

	return (count);
}

/**
 * dup_char - duplicates character
 * @path_str: PATH string
 * @start: start index
 * @stop: end index
 *
 * Return: pointer to new buffer
 */
char *dup_char(char *path_str, int start, int stop)
{
	int i = 0, j = 0;
	static char buffer[1024];

	for (j = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buffer[j++] = path_str[i];
	buffer[j] = 0;

	return (buffer);
}

/**
 * print_list_dir - prints only the dir member of list_t
 * @h: pointer to head-node
 *
 * Return: size of list
 */
size_t print_list_dir(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(h->dir ? h->dir : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}

	return (index);
}

/**
 * print_list_t - prints all elements of a list_t linked list
 * @head: pointer to head-node
 *
 * Return: size of list
 */
size_t print_list_t(const list_t *head)
{
	size_t index = 0;

	while (head)
	{
		_puts(convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->dir ? head->dir : "(nil)");
		_puts("\n");
		head = head->next;
		index++;
	}

	return (index);
}

/**
 * prt_alias - prints alias
 * @list: the alias node
 *
 * Return: 0 on success or 1 on error
 */
int prt_alias(list_t *list)
{
	char *ptr = NULL;
	char *a = NULL;

	if (list)
	{
		ptr = _strchr(list->dir, '=');
		for (a = list->dir; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

