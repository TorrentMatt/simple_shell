#include "header.h"

/**
 * _myenv - Will print the enironment
 * @inf: Struct that has arguments
 * Return: Always 0
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenv - Will give out the value of environment variable
 * @inf: Struct contain arguments.
 * @nme:enironment variable
 * Return: null
 */
char *_getenv(info_t *inf, const char *nme)
{
	list_t *nde = inf->env;
	char *t;

	while (nde)
	{
		t = starts_with(nde->str, nme);
		if (t && *t)
			return (t);
		nde = nde->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Will initialize new environment or modify existing one
 * @inf: Struct contain potential arguments
 *  Return:0
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Number of arguements is incorrect or wrong\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -Will remove environment variable
 * @inf: Struct contain potential arguments
 * Return: 0
 */
int _myunsetenv(info_t *inf)
{
	int t;

	if (inf->argc == 1)
	{
		_eputs("The are few arguements.\n");
		return (1);
	}
	for (t = 1; t <= inf->argc; t++)
		_unsetenv(inf, inf->argv[t]);

	return (0);
}

/**
 * populate_env_list - Will populate environment linked list
 * @inf: Struct contain potential arguments
 * Return: 0
 */
int populate_env_list(info_t *inf)
{
	list_t *nde = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_end(&nde, environ[t], 0);
	inf->env = nde;
	return (0);
}

