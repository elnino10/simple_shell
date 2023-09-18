#include "main.h"

/**
 * interactive_mode - returns true if shell is interactive mode
 * @information: struct address
 *
 * Return: 1 if interactive_mode is true and 0 otherwise
 */
int interactive_mode(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);

}

/**
 * replace_str - replaces string
 * @old_str: pointer to address of old string
 * @new_str: pointer to the new string
 *
 * Return: 1 if replaced and 0 otherwise
 */
int replace_str(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;

	return (1);
}

/**
 * convert_num - number converter function, like itoa
 * @num: number to convert
 * @base: base
 * @flag: argument flag
 *
 * Return: string pointer
 */
char *convert_num(long int num, int base, int flag)
{
	static char buff[50];
	static char *arr;
	char *str;
	char sign = 0;
	unsigned long n = num;

	if (!(flag & UNSIGNED_CONVERTER) && num < 0)
	{
		n = -num;
		sign = '-';

	}

	arr = flag & LOWERCASE_CONVERTER ? "0123456789abcdef" : "0123456789ABCDEF";
	str = &buff[49];
	*str = '\0';

	do	{
		*--str = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--str = sign;

	return (str);
}

/**
 * is_delimitter - checks if character is a delimitter
 * @ch: character to check
 * @delimitter: delimeter string
 *
 * Return: 1 if true or 0 if not true
 */
int is_delimitter(char ch, char *delimitter)
{
	while (*delimitter)
		if (*delimitter++ == ch)
			return (1);
	return (0);
}

/**
 * path_finder - finds command in PATH string
 * @info: info struct
 * @path_str: PATH string
 * @cmd: cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *path_finder(info_t *info, char *path_str, char *cmd)
{
	char *path;
	int i = 0, curr_pos = 0;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_str(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_char(path_str, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

