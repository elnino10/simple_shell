#include "main.h"

/**
 * _unsetenv - unsets environment variable
 * @info: Structure containing potential arguments
 * @var: string environment variable property
 *
 *  Return: 1 on delete or 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	size_t index = 0;
	char *p;
	list_t *list = info->env;

	if (!list || !var)
		return (0);

	while (list)
	{
		p = start_str(list->dir, var);
		if (p && *p == '=')
		{
			info->env_changed = del_node_at_index(&(info->env), index);
			index = 0;
			list = info->env;
			continue;
		}
		list = list->next;
		index++;
	}

	return (info->env_changed);
}
