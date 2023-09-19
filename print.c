#include "main.h"

/**
 * _putchar - writes ch to stdout
 * @ch: Character to be printed
 *
 * Return: On success 1
 * On error -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUFFER_SZ];

	if (ch == BUFFER_FLUSH || i >= WRITE_BUFFER_SZ)
	{
		write(1, buf, i);
		i = 0;
	}

	if (ch != BUFFER_FLUSH)
		buf[i++] = ch;

	return (1);
}

/**
 *_puts - prints an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 *_putsfd - prints input string
 * @s: string to be printed
 * @fd: file descriptor
 *
 * Return: the number of chars put
 */
int _putsfd(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putcharfd(*s++, fd);
	}
	return (i);
}

/**
 * _putcharfd - writes character c to fd
 * @c: character to print
 * @fd: file descriptor
 *
 * Return: On success 1.
 * On error -1 is returned, and errno is set appropriately.
 */
int _putcharfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SZ];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SZ)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buf[i++] = c;
	return (1);
}

