#include "main.h"

/**
 * _strlen - returns the length of a string
 * Return: 0 (success)
 * @s: pointer variable
 */
int _strlen(char *s)
{
	int i, len;

	len = 0;
	for (i = 0; s[i] != '\0'; i++)
	{
		len++;
	}
	return (len);
}

/**
 * _strcat - concatenates two strings
 * @dest: desination file
 * @src: source file
 * Return: returns a pointer to dest
 */
char *_strcat(char *dest, char *src)
{
	int i, len;
	char *ptr = dest;

	i = 0;
	len = _strlen(dest);
	while (src[i] != '\0')
	{
		dest[len] = src[i];
		len++;
		i++;
	}
	dest[len] = '\0';
	return (ptr);
}

/**
 * _strcmp - compare two strings
 * @s1: string one
 * @s2: string two
 * Return: 0 is equal, negative if s1 < s2 and positive value if s1 > s2
 */
int _strcmp(char *s1, char *s2)
{
	int i, val, flag;

	val = 0;
	flag = 0;
	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; ++i)
	{
		if (s1[i] == s2[i])
		{
			flag = 0;
		}
		else
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		val = 0;
	}
	else
	{
		val = s1[i] - s2[i];
	}
	return (val);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @str: pointer to string to be duplicated
 *
 * Return: pointer to duplicate string
 */
char *_strdup(const char *str)
{
	int i, len;
	char *s;

	i = 0;
	len = 0;

	if (str == NULL)
		return (NULL);
	while (str[len])
	len++;

	s = malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);

	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

/**
 * _strcpy -copies string from one file to another
 * @dest: destination file
 * @src: source file
 * Return: return the copied file
 */
char *_strcpy(char *dest, char *src)
{
	char *mainDest = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (mainDest);
}
