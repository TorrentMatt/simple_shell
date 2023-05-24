#include "header.h"

/**
 * _strlen - Function will return the length of a string
 * @s: String 
 * Return: Return length of string integer 
 */
int _strlen(char *s)
{
	int t = 0;

	if (!s)
		return (0);

	while (*s++)
		t++;
	return (t);
}

/**
 * _strcmp - Function will perform lexicogarphic comparison between two strangs.
 * @str1: string number 1
 * @str2: string number 2
 * Return: Return negative if str1 is less str2, positive if str1 > s2, zero if s1 == s2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - Function will check if for needle
 * @hstack: stringfor search
 * @needle: needle to  find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *hstack, const char *needle)
{
	while (*needle)
		if (*needle++ != *hstack++)
			return (NULL);
	return ((char *)hstack);
}

/**
 * _strcat - Functiom will concatenates two strings
 * @destx: Destination
 * @src: the source
 *
 * Return: Return pointer to destination buffer
 */
char *_strcat(char *destx, char *src)
{
	char *ret = destx;

	while (*destx)
		destx++;
	while (*src)
		*destx++ = *src++;
	*destx = *src;
	return (ret);
}

