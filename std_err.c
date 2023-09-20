#include "main.h"

/**
 * err_putchar - writes ch to stderr
 * @ch: Character to be printed
 *
 * Return: On success 1
 * On error -1 is returned, and errno is set appropriately.
 */
int err_putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUFFER_SZ];

	if (ch == BUFFER_FLUSH || i >= WRITE_BUFFER_SZ)
	{
		write(2, buf, i);
		i = 0;
	}

	if (ch != BUFFER_FLUSH)
		buf[i++] = ch;

	return (1);
}

/**
 *err_puts - prints an input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void err_puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		err_putchar(str[i]);
		i++;
	}
}

/**
 * print_err - prints error message
 * @info: info_t struct
 * @str: string containing specified error
 *
 * Return: 0 if no numbers str, converted number otherwise
 *        -1 on error
 */
void print_err(info_t *info, char *str)
{
	err_puts(info->fname);
	err_puts(": ");
	print_dec(info->line_count, STDERR_FILENO);
	err_puts(": ");
	err_puts(info->argv[0]);
	err_puts(": ");
	err_puts(str);
}

