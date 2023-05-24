#include "header.h"

/**
 **_strncpy - Function will copy a string
 *@destx: Destination of string to be copied 
 *@src: source string
 *@num: the amount of characters to be copied
 *Return: String concatenated
 */
char *_strncpy(char *destx, char *src, int num)
{
	int t, p;
	char *x = destx;

	t = 0;
	while (src[t] != '\0' && t < num - 1)
	{
		destx[t] = src[t];
		t++;
	}
	if (t < num)
	{
		p = t;
		while (p < num)
		{
			destx[t] = '\0';
			p++;
		}
	}
	return (x);
}

/**
 **_strncat - Function will concatenate two strings
 *@destx:  First string of concation
 *@src: Second string
 *@num: Amount of bytes to be used
 *Return: Concatenated string
 */
char *_strncat(char *destx, char *src, int num)
{
	int t, p;
	char *e = destx;

	t = 0;
	p = 0;
	while (destx[t] != '\0')
		t++;
	while (src[p] != '\0' && p < num)
	{
		destx[t] = src[p];
		t++;
		p++;
	}
	if (p < num)
		destx[t] = '\0';
	return (e);
}

/**
 **_strchr - Function will locate character in a string
 *@sp: String  parsed
 *@c:  character to look for 
 *Return: sp
 */
char *_strchr(char *sp, char c)
{
	do {
		if (*sp == c)
			return (sp);
	} while (*sp++ != '\0');

	return (NULL);
}

