#include "header.h"

/**
 * _strcpy - Function will copy string
 * @destx: Destination
 * @src: Source
 * Return:Return pointer to destination
 */
char *_strcpy(char *destx, char *src)
{
	int t = 0;

	if (destx == src || src == 0)
		return (destx);
	while (src[t])
	{
		destx[t] = src[t];
		t++;
	}
	destx[t] = 0;
	return (destx);
}

/**
 * _strdup - Function will duplicate string
 * @str: string 
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int ln = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		ln++;
	ret = malloc(sizeof(char) * (ln + 1));
	if (!ret)
		return (NULL);
	for (ln++; ln--;)
		ret[ln] = *--str;
	return (ret);
}

/**
 * _puts - Function will print string input
 * @str: String
 * Return: Nothing
 */
void _puts(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		_putchar(str[t]);
		t++;
	}
}

/**
 * _putchar - Function will write the c to stdout
 * @c: character 
 * Return: Returns on success 1 andn error, -1 is returned
 */
int _putchar(char c)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(1, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

