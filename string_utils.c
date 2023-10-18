#include "main.h"

/**
 * _strlen - This function returns the nbr of char in str
 * @str: string input
 * Return: nbr of char in str.
 */

unsigned int _strlen(char *str)
{
	unsigned int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}


/**
 * _strcmp - This compares two strings.
 * @s1: This is an input const string
 * @s2: defined as an input const string
 *
 * Return: returns an integer indicating the result of the comparison,
 * as follows:
 * 0, if the s1 and s2 are equal
 * a negative value if s1 is less than s2
 * a positive value if s1 is greater than s2
 */
int _strcmp(const char *s1, const char *s2)
{
	int i;
	int res = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
		{
			res = s1[i] - s2[i];
			break;
		}
	}

	return (res);
}

/**
 * _strncmp - This function compares two strings.
 * @s1: an input const string
 * @s2: an input const string
 * @n: an input int
 *
 * Return: returns an integer indicating the result of the comparison,
 * as follows:
 * 0, if the s1 and s2 are equal
 * a negative value if s1 is less than s2
 * a positive value if s1 is greater than s2
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i;
	int res = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{

		if (i >= n)
			break;
		if (s1[i] != s2[i])
		{
			res = s1[i] - s2[i];
			break;
		}
	}

	return (res);
}

/**
 * _strcpy - A function to copy src to dest.
 * @dest: an input char *
 * @src: an input const char *
 * Return: char *
 */
char *_strcpy(char *dest, const char *src)
{
	int len;

	for (len = 0; src[len] != '\0'; ++len)
	{
		dest[len] = src[len];
	}
	dest[len] = '\0';
	return (dest);
}

/**
 * _strcat-  A funct. that appends the src string to the dest string.
 * @dest: An input string
 * @src: An input const string
 * Return: void
 */
char *_strcat(char *dest, const char *src)
{
	char *result = dest;

	while (*dest != '\0')
		dest++;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';

	return (result);
}
