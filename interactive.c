#include "header.h"

/**
 * interactive -Function will return true if shell is in interactive mode
 * @info: struct paramenter
 * Return:Retun 1 if interactive mode or 0 if not
 */
int interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delim - Function will check for character in a delimeter
 * @cht: charater
 * @delim: Delimeter strings
 * Return: Return 1 if true, 0 if false
 */
int is_delim(char cht, char *delim)
{
	while (*delim)
		if (*delim++ == cht)
			return (1);
	return (0);
}

/**
 * _isalpha - Function will perform check for alphabetic character
 * @cht: Character
 * Return: Returns 1 if cht is alphabetic, 0 otherwise
 */

int _isalpha(int cht)
{
	if ((cht >= 'a' && cht <= 'z') || (cht >= 'A' && cht <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Fuction will process converts of string to an integer
 * @sg: String
 * Return:Return 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *sg)
{
	int t, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (t = 0; sg[t] != '\0' && flag != 2; t++)
	{
		if (sg[t] == '-')
			sign *= -1;

		if (sg[t] >= '0' && sg[t] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (sg[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}

