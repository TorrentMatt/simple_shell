#include "header.h"

/**
 * _erratoi - Will convert strings to integers
 * @p: string  converted to int
 * Return: 0,or converted number and -1 for error
 */
int _erratoi(char *p)
{
	int t = 0;
	unsigned long int res = 0;

	if (*p == '+')
		p++; 
	for (t = 0;  p[t] != '\0'; t++)
	{
		if (p[t] >= '0' && p[t] <= '9')
		{
			res *= 10;
			res += (p[t] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error -  Will print error message
 * @info_p: Is the parameter and return info struct
 * @tstr: string
 * Return: will return 0 if no numbers in string or converted number otherwise -1 on error
 */
void print_error(info_t *info_p, char *tstr)
{
	_eputs(info_p->fname);
	_eputs(": ");
	print_d(info_p->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info_p->argv[0]);
	_eputs(": ");
	_eputs(tstr);
}

/**
 * print_d -Will prints  decimal  number 
 * @inp: the input 
 * @fd: filedescriptor
 * Return:characters printed
 */
int print_d(int inp, int fd)
{
	int (*__putchar)(char) = _putchar;
	int t, cnt = 0;
	unsigned int _ab_, crent;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (inp < 0)
	{
		_ab_ = -inp;
		__putchar('-');
		cnt++;
	}
	else
		_ab_ = inp;
	crent = _ab_;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_ab_ / t)
		{
			__putchar('0' + crent / t);
			cnt++;
		}
		crent %= t;
	}
	__putchar('0' + crent);
	cnt++;

	return (cnt);
}

/**
 * convert_number - Will converter numbers
 * @numb: the number
 * @base: the base
 * @flg:the argument flags
 * Return:the string
 */
char *convert_number(long int numb, int base, int flg)
{
	static char *array;
	static char buffer[50];
	char sgn = 0;
	char *ptnr;
	unsigned long n = numb;

	if (!(flg & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sgn = '-';

	}
	array = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptnr = &buffer[49];
	*ptnr = '\0';

	do	{
		*--ptnr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sgn)
		*--ptnr = sgn;
	return (ptnr);
}

/**
 * remove_comments - Will replaces  instance of '#' with '\0'
 * @bufp: Address of string to be modify
 * Return: 0
 */
void remove_comments(char *bufp)
{
	int t;

	for (t = 0; bufp[t] != '\0'; t++)
		if (bufp[t] == '#' && (!t || bufp[t - 1] == ' '))
		{
			bufp[t] = '\0';
			break;
		}
}

