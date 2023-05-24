#include "header.h"

/**
 * _myhistory - Function will display the history list
 * @inf: Struct parameter
 *  Return: 0
 */
int _myhistory(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unset_alias - Function will set alias to string
 * @inf: parameter struct
 * @strx: the string alias
 * Return: Return 0 on success, 1 on error
 */
int unset_alias(info_t *inf, char *strx)
{
	char *x, o;
	int ret;

	x = _strchr(strx, '=');
	if (!x)
		return (1);
	o = *x;
	*x = 0;
	ret = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, strx, -1)));
	*x = o;
	return (ret);
}

/**
 * set_alias -Fucntion will  set alia to string
 * @inf: Struct parameter
 * @strx: the string alias
 * Return: Return 0 on success, 1 on error
 */
int set_alias(info_t *inf, char *strx)
{
	char *p;

	p = _strchr(strx, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(inf, strx));

	unset_alias(inf, strx);
	return (add_node_end(&(inf->alias), strx, 0) == NULL);
}

/**
 * print_alias - Will print alias
 * @nde: the alias node
 * Return: Returns 0 on success, 1 on error
 */
int print_alias(list_t *nde)
{
	char *x = NULL, *a = NULL;

	if (nde)
	{
		x = _strchr(nde->str, '=');
		for (a = nde->str; a <= x; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @inf: Struct parameter
 *  Return: 0
 */
int _myalias(info_t *inf)
{
	int t = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (t = 1; inf->argv[t]; t++)
	{
		p = _strchr(inf->argv[t], '=');
		if (p)
			set_alias(inf, inf->argv[t]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[t], '='));
	}

	return (0);
}

