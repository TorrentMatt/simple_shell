#include "header.h"

/**
 * _memset - Function will fill up memory with a constant bytes
 * @sp: pointer 
 * @b: bytes
 * @num: number of bytes
 * Return:Return a pointer to the memory area 
 */
char *_memset(char *sp, char b, unsigned int num)
{
	unsigned int t;

	for (t = 0; t < num; t++)
		sp[t] = b;
	return (sp);
}

/**
 * ffree - Function will free up string of strings
 * @pp: string 
 */
void ffree(char **pp)
{
	char **p = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(p);
}

/**
 * _realloc -Function will relocate  block of memory
 * @ptr: pointer 
 * @old_size: byte 
 * @new_size: byte
 * Return:Return pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *a;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	a = malloc(new_size);
	if (!a)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		a[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (a);
}

