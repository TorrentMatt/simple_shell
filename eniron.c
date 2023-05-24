#include "header.h"

/**
 * get_environ - Fuction will return string array copy of environment
 * @inf: Struct parameter
 * Return: 0
 */
char **get_environ(info_t *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * _unsetenv - Function will remove environment variables
 * @inf: Struct parameter
 * @var: the string env var property 
 * Return:Return 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *inf, char *var)
{
	list_t *nde = inf->env;
	size_t t = 0;
	char *p;

	if (!nde || !var)
		return (0);

	while (nde)
	{
		p = starts_with(nde->str, var);
		if (p && *p == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), t);
			t = 0;
			nde = inf->env;
			continue;
		}
		nde = nde->next;
		t++;
	}
	return (inf->env_changed);
}

/**
 * _setenv - Function initialize a new environment variable, or modify an existing one
 * @inf: Struct parameter
 * @var: string of environment
 * @val: string of environment
 *  Return: Always 0
 */
int _setenv(info_t *inf, char *var, char *val)
{
	char *buf = NULL;
	list_t *nde;
	char *o;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	nde = inf->env;
	while (nde)
	{
		o = starts_with(nde->str, var);
		if (o && *o == '=')
		{
			free(nde->str);
			nde->str = buf;
			inf->env_changed = 1;
			return (0);
		}
		nde = nde->next;
	}
	add_node_end(&(inf->env), buf, 0);
	free(buf);
	inf->env_changed = 1;
	return (0);
}


