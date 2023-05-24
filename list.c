#include "header.h"

/**
 * add_node - Function will add  nodes to the start of the list
 * @h: the head node
 * @str: string node
 * @num:  node index 
 *
 * Return: Return size of list
 */
list_t *add_node(list_t **h, const char *str, int num)
{
	list_t *new_head;

	if (!h)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *h;
	*h = new_head;
	return (new_head);
}

/**
 * add_node_end - Function will add node to the end of the list
 * @h: head node
 * @str: string node
 * @num: node index
 * Return: Return size of list
 */
list_t *add_node_end(list_t **h, const char *str, int num)
{
	list_t *new_node, *nde;

	if (!h)
		return (NULL);

	nde = *h;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (nde)
	{
		while (nde->next)
			nde = nde->next;
		nde->next = new_node;
	}
	else
		*h = new_node;
	return (new_node);
}

/**
 * print_list_str - Function will print only the string element of a list_t linked list
 * @h: first node
 * Return: Return size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t t = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(null)");
		_puts("\n");
		h = h->next;
		t++;
	}
	return (t);
}

/**
 * delete_node_at_index - Function will delete node at given index
 * @h: first node
 * @index: index of node
 * Return: Return 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **h, unsigned int index)
{
	list_t *nde, *prev_node;
	unsigned int t = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		nde = *h;
		*h = (*h)->next;
		free(nde->str);
		free(nde);
		return (1);
	}
	nde = *h;
	while (nde)
	{
		if (t == index)
		{
			prev_node->next = nde->next;
			free(nde->str);
			free(nde);
			return (1);
		}
		t++;
		prev_node = nde;
		nde = nde->next;
	}
	return (0);
}

/**
 * free_list - Function will free all nodes of a list
 * @head_ptr: pointer to head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *nde, *next_node, *h;

	if (!head_ptr || !*head_ptr)
		return;
	h = *head_ptr;
	nde = h;
	while (nde)
	{
		next_node = nde->next;
		free(nde->str);
		free(nde);
		nde = next_node;
	}
	*head_ptr = NULL;
}

