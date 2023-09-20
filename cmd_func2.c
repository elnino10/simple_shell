#include "main.h"

/**
 * __unsetenv - unsets environment variable
 * @info: Structure containing potential arguments
 *
 *  Return: 0
 */
int __unsetenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_puts("Too few arguments.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		_unsetenv(info, info->argv[index]);

	return (0);
}

/**
 * __cd - changes current directory of process
 * @info: Structure containing potential arguments
 *
 *  Return: 0
 */
int __cd(info_t *info)
{
	int chdir_ret_val;
	char buffer[1024], *dir, *str;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure errmsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret_val = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret_val = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret_val =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret_val = chdir(info->argv[1]);
	if (chdir_ret_val == -1)
	{
		print_error(info, "cannot cd to ");
		_puts(info->argv[1]), _putchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * __alias - works like alias built-in
 * @info: Structure containing potential arguments
 *
 *  Return: 0
 */
int __alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *list = NULL;

	if (info->argc == 1)
	{
		list = info->alias;
		while (list)
		{
			prt_alias(list);
			list = list->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			prt_alias(node_prefix(info->alias, info->argv[i], '='));
	}
	return (0);
}

/**
 * set_alias - sets string alias
 * @info: parameter struct
 * @string: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *string)
{
	char *al_ptr;

	al_ptr = _strchr(string, '=');
	if (!al_ptr)
		return (1);
	if (!*++al_ptr)
		return (reset_alias(info, string));
	reset_alias(info, string);
	return (add_node_end(&(info->alias), string, 0) == NULL);
}

/**
 * reset_alias - unsets alias
 * @info: parameter struct
 * @string: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int reset_alias(info_t *info, char *string)
{
	char *ptr, ch;
	int ret_val;

	ptr = _strchr(string, '=');
	if (!ptr)
		return (1);

	ch = *ptr;
	*ptr = 0;
	ret_val = del_node_at_index(&(info->alias),
			get_node_ind(info->alias, node_prefix(info->alias, string, -1)));
	*ptr = ch;
	return (ret_val);
}
