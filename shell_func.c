#include "main.h"

/**
 * hsh - shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main.c function
 *
 * Return: 0 on success and 1 on error, or error code
 */
int hsh(info_t *info, char **argv)
{
	int built_in_ret = 0;
	ssize_t ret_val = 0;

	while (built_in_ret != -2 && ret_val != -1)
	{
		clr_info(info);
		if (interactive_mode(info))
			_puts("$ ");
		_putchar(BUFFER_FLUSH);
		ret_val = user_input(info);
		if (ret_val != -1)
		{
			set_info(info, argv);
			built_in_ret = get_built_in(info);
			if (built_in_ret == -1)
				find_command(info);
		}
		else if (interactive_mode(info))
			_putchar('\n');
		free_info(info, 0);
	}
	wrt_history(info);
	free_info(info, 1);
	if (!interactive_mode(info) && info->status)
		exit(info->status);
	if (built_in_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_in_ret);
}

/**
 * get_built_in - gets a built-in command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found
 *			0 if builtin executed successfully
 *			1 if builtin found but not successful
 *			-2 if builtin signals exit
 */
int get_built_in(info_t *info)
{
	int built_in_ret = -1, index;
	built_in_table table[] = {
		{"alias", __alias},
		{"cd", __cd},
		{"exit", __exit},
		{"env", __env},
		{"history", __history},
		{NULL, NULL}
	};

	for (index = 0; table[index].type; index++)
	{
		if (_strcmp(info->argv[0], table[index].type) == 0)
		{
			info->line_count++;
			built_in_ret = table[index].func(info);
			break;
		}
	}

	return (built_in_ret);
}

/**
 * find_command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_command(info_t *info)
{
	int i, j;
	char *cmd_path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
	{
		if (!is_delimitter(info->arg[i], " \t\n"))
			j++;
	}
	if (!j)
		return;
	cmd_path = path_finder(info, _getenv(info, "PATH="), info->argv[0]);
	if (cmd_path)
	{
		info->path = cmd_path;
		fork_command(info);
	}
	else
	{
		if ((interactive_mode(info) || _getenv(info, "PATH=") ||
		info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * fork_command - forks exec thread to run cmd in child
 * @info: info_t struct
 *
 * Return: nothing
 */
void fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_env(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
