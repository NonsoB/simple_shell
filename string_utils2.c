#include "main.h"

/**
 * _strdup - This function returns a pointer to a newly allocated
 * space in memory, which contains a copy of the string given as a parameter.
 * @str: a string input
 * Return: pointer
 */
char *_strdup(const char *str)
{
	int i, len = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	result = (char *)malloc((len + 1) * sizeof(char));

	if (result == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		result[i] = str[i];

	return (result);
}


/**
 * _isnumber - This function will check if a string is a number
 * @status: A string to be checked
 * Return: void
 */
int _isnumber(const char *status)
{
	if (status == NULL || status[0] == '\0')
		return (0);
	while (*status)
	{
		if (!_isdigit(*status))
			return (0);
		status++;
	}
	return (1);
}


/**
 * _isdigit - This will check if charachter is number
 * @c: a charachter
 * Return: 1 if its a digit 0 otherwise
 */
int _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
