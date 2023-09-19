#include "main.h"

/**
 * get_path - gets the directory of the command
 * @command: command-line command
 *
 * Return: pointer to the directory/path for command
 */
char *get_path(char *command)
{
	char *path, *path_cpy, *token, *file_path;
	int command_len, dir_len;
	struct stat buff;

	path = getenv("PATH");
	if (path)
	{
		path_cpy = strdup(path);

		command_len = strlen(command);
		/*tokenize the duplicate of path string*/
		token = strtok(path_cpy, ":");
		while (token)
		{
			dir_len = strlen(token);
			file_path = malloc(dir_len + command_len + 2);
			/*makes file_path a null-terminated full path with entered command*/
			strcpy(file_path, token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			/*tests if file_path exists else try next path*/
			if (stat(file_path, &buff) == 0)
			{
				return (file_path);
			}
			else
			{
				free(file_path);
				token = strtok(NULL, ":");
			}
		}
		/*before returning, free path_cpy and check if command is a file_path*/
		free(path_cpy);
		if (stat(command, &buff) == 0)
			return (command);
		return (NULL);
	}
	return (NULL);
}

