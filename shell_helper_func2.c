#include "main.h"

/**
 * _atoi - converts string to integer
 * @str: the string to be converted
 *
 * Return: 0 if no numbers in str, converted number otherwise
 *       -1 on error
 */
int _atoi(char *str)
{
	unsigned long int res = 0;
	int index = 0;

	if (*str == '+')
		str++;
	for (index = 0;  str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			res *= 10;
			res += (str[index] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (res);
}

