#include "main.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 when success or 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { _INIT_ };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_puts(argv[0]);
				_puts(": 0: Can't open ");
				_puts(argv[1]);
				_putchar('\n');
				_putchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	create_env_list(info);
	rd_history(info);
	hsh(info, argv);

	return (EXIT_SUCCESS);
}

