#include "main.h"

/**
 * start_str - checks if needle starts with str
 * @str: string to search for
 * @needle: the substring to find
 *
 * Return: address of next char of str or NULL
 */
char *start_str(const char *str, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *str++)
			return (NULL);
	}
	return ((char *)str);
}

/**
 **_strchr - finds character in a string
 *@str: the string to be parsed
 *@ch: the character to look for

 *Return: pointer to the memory area str
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}

/**
 **_strncat - concatenates two strings
 *@des: destination string
 *@src: source string
 *@num: the amount of bytes to be maximally used
 *
 *Return: the concatenated string
 */
char *_strncat(char *des, char *src, int num)
{
	int i, j;
	char *str = des;

	i = 0;
	j = 0;
	while (des[i] != '\0')
		i++;

	while (src[j] != '\0' && j < num)
	{
		des[i] = src[j];
		i++;
		j++;
	}

	if (j < num)
		des[i] = '\0';

	return (str);
}

/**
 **_strncpy - copies a string
 *@des: destination string
 *@src: source string
 *@num: number of characters to be copied
 *
 *Return: copied string
 */
char *_strncpy(char *des, char *src, int num)
{
	int i, j;
	char *str = des;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		des[i] = src[i];
		i++;
	}

	if (i < num)
	{
		j = i;
		while (j < num)
		{
			des[j] = '\0';
			j++;
		}
	}
	return (str);
}

/**
 * _strtok_func - splits a string into words. Repeat delimiters are ignored
 * @str: input string
 * @delim: delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtok_func(char *str, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimitter(str[i], delim) &&
				(is_delimitter(str[i + 1], delim) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimitter(str[i], delim))
			i++;
		k = 0;
		while (!is_delimitter(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;

	return (s);
}
