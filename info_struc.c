#include "header.h"

/**
 * clear_info - Fuction will initialize info_t struct
 * @inf: Struct parameter
 */
void clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info -Fuction will initialize info_t struct
 * @inf: Struct parameter
 * @av: Argument vector
 */
void set_info(info_t *inf, char **av)
{
	int t = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (t = 0; inf->argv && inf->argv[t]; t++)
			;
		inf->argc = t;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_info - function will free up info_t struct fields
 * @info: struct parameter
 * @all: freeing all fields
 */
void free_info(info_t *inf, int all)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FLUSH);
	}
}

