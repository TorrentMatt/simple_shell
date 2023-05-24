#include "header.h"

/**
 * _eputs - will print  input string
 * @str_p: string to be printed
 * Return: 0
 */
void _eputs(char *str_p)
{
	int t = 0;

	if (!str_p)
		return;
	while (str_p[t] != '\0')
	{
		_eputchar(str_p[t]);
		t++;
	}
}

/**
 * _eputchar -will write character stderr
 * @p:print character
 * Return:will return success 1 on error, -1 is returned.
 */
int _eputchar(char p)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(2, buf, t);
		t = 0;
	}
	if (p != BUF_FLUSH)
		buf[t++] = p;
	return (1);
}

/**
 * _putfd - Will writecharacter p to given fd
 * @p: print character 
 * @fd: This is  filedescriptor 
 * Return: Return 1 success -1 is returned on error.
 */
int _putfd(char p, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(fd, buf, t);
		t = 0;
	}
	if (p != BUF_FLUSH)
		buf[t++] = p;
	return (1);
}

/**
 * _putsfd -Will print input string
 * @str_p: string printed
 * @fd: filedescriptor
 * Return:0
 */
int _putsfd(char *str_p, int fd)
{
	int t = 0;

	if (!str_p)
		return (0);
	while (*str_p)
	{
		t += _putfd(*str_p++, fd);
	}
	return (t);
}

