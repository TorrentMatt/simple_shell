#include "header.h"

/**
 * **strtow - Function will split string into words
 * @str: string
 * @delimeter: delimeter string
 * Return:Return pointer to an array of strings or NULL on failure
 */

char **strtow(char *str, char *delimeter)
{
	int t, j, k, m, numwords = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (t = 0; str[t] != '\0'; t++)
		if (!is_delim(str[t], delimeter) && (is_delim(str[t + 1], delimeter) || !str[t + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	x = malloc((1 + numwords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (t = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[t], delimeter))
			t++;
		k = 0;
		while (!is_delim(str[t + k], delimeter) && str[t + k])
			k++;
		x[j] = malloc((k + 1) * sizeof(char));
		if (!x[j])
		{
			for (k = 0; k < j; k++)
				free(x[k]);
			free(x);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			x[j][m] = str[t++];
		x[j][m] = 0;
	}
	x[j] = NULL;
	return (x);
}

/**
 * **strtow2 - Fuction will split string into words
 * @str: string
 * @delimeter: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char delimeter)
{
	int t, j, k, m, numwords = 0;
	char **x;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (t = 0; str[t] != '\0'; t++)
		if ((str[t] != delimeter && str[t + 1] == delimeter) ||
				    (str[t] != delimeter && !str[t + 1]) || str[t + 1] == delimeter)
			numwords++;
	if (numwords == 0)
		return (NULL);
	x = malloc((1 + numwords) * sizeof(char *));
	if (!x)
		return (NULL);
	for (t = 0, j = 0; j < numwords; j++)
	{
		while (str[t] == delimeter && str[t] != delimeter)
			t++;
		k = 0;
		while (str[t + k] != delimeter && str[t + k] && str[t + k] != delimeter)
			k++;
		x[j] = malloc((k + 1) * sizeof(char));
		if (!x[j])
		{
			for (k = 0; k < j; k++)
				free(x[k]);
			free(x);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			x[j][m] = str[t++];
		x[j][m] = 0;
	}
	x[j] = NULL;
	return (x);
}

