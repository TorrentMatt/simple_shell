#include "header.h"

/**
 * is_chain - Function will test if current char in buffer is a chain delimeter
 * @inf: Struct parameter
 * @buf: buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *inf, char *buf, size_t *p)
{
	size_t t = *p;

	if (buf[t] == '|' && buf[t + 1] == '|')
	{
		buf[t] = 0;
		t++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buf[t] == '&' && buf[t + 1] == '&')
	{
		buf[t] = 0;
		t++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[t] == ';') 
	{
		buf[t] = 0; 
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = t;
	return (1);
}

/**
 * check_chain - Function will check if it should continue chaining based on last status
 * @inf: stuct parameter
 * @buf: buffer
 * @p: current position in buf
 * @i: position in buf
 * @len: length 
 * Return: Void
 */
void check_chain(info_t *inf, char *buf, size_t *p, size_t i, size_t len)
{
	size_t t = *p;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[i] = 0;
			t = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[i] = 0;
			t = len;
		}
	}

	*p = t;
}

/**
 * replace_alias - function will replace all aliases in the tokenized string
 * @inf: Struct parameter
 * Return: Return 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *inf)
{
	int t;
	list_t *nde;
	char *p;

	for (t = 0; t < 10; t++)
	{
		nde = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!nde)
			return (0);
		free(inf->argv[0]);
		p = _strchr(nde->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Function will replace vars in tokenized string
 * @inf: Struct prarmeeter
 * Return: Return 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *inf)
{
	int t = 0;
	list_t *nde;

	for (t = 0; inf->argv[t]; t++)
	{
		if (inf->argv[t][0] != '$' || !inf->argv[t][1])
			continue;

		if (!_strcmp(inf->argv[t], "$?"))
		{
			replace_string(&(inf->argv[t]),
					_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[t], "$$"))
		{
			replace_string(&(inf->argv[t]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nde = node_starts_with(inf->env, &inf->argv[t][1], '=');
		if (nde)
		{
			replace_string(&(inf->argv[t]),
					_strdup(_strchr(nde->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[t], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Function will replace string
 * @old: old string
 * @new: new string
 * Return: eturn 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

