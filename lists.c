#include "header.h"

/**
 * list_len - Function will determine length of linked list
 * @h: first node
 * Return: Return size of list
 */
size_t list_len(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		h = h->next;
		t++;
	}
	return (t);
}

/**
 * list_to_strings - Function will return an array of strings of the list->str
 * @head: first node
 * Return: Return array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *nde = head;
	size_t t = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !t)
		return (NULL);
	strs = malloc(sizeof(char *) * (t + 1));
	if (!strs)
		return (NULL);
	for (t = 0; nde; nde = nde->next, t++)
	{
		str = malloc(_strlen(nde->str) + 1);
		if (!str)
		{
			for (j = 0; j < t; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, nde->str);
		strs[t] = str;
	}
	strs[t] = NULL;
	return (strs);
}


/**
 * print_list -Function will print all elements of a list_t linked list
 * @h: first node
 * Return: Return size of list
 */
size_t print_list(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		t++;
	}
	return (t);
}

/**
 * node_starts_with - Function will return node string starts with prefix
 * @node: list head
 * @prefix: string 
 * @c: Return the next character after prefix to match
 * Return: Return match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *x = NULL;

	while (node)
	{
		x = starts_with(node->str, prefix);
		if (x && ((c == -1) || (*x == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Function will get index of a node
 * @head: list head
 * @node: pointer
 * Return: Return index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t t = 0;

	while (head)
	{
		if (head == node)
			return (t);
		head = head->next;
		t++;
	}
	return (-1);
}

