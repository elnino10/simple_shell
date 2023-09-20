#include "main.h"

/**
 * __exit - exits shell
 * @info: Structure with arguments
 *
 * Return: exits with a given exit status
 */
int __exit(info_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = _atoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			_puts(info->argv[1]);
			_putchar('\n');
			return (1);
		}
		info->err_num = _atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * __env - prints current environment variables
 * @info: Structure with potential arguments. Used to maintain
 * constant function prototype
 *
 * Return: Always 0
 */
int __env(info_t *info)
{
	print_list_dir(info->env);

	return (0);
}

/**
 * __help - changes current directory of process
 * @info: Structure with potential arguments
 *
 * Return: 0
 */
int __help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);

	return (0);
}

/**
 * __history - displays history list, one command by line, preceeded
 * with line numbers, starting at 0
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype
 *
 * Return: Always 0
 */
int __history(info_t *info)
{
	print_list_t(info->history);

	return (0);
}

/**
 * __setenv - sets new environment variable,
 * or modify existing one
 * @info: Structure containing potential arguments
 *
 * Return: 0
 */
int __setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}
