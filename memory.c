#include "header.h"

/**
 * bfree - Function will frees up a pointer and NULLs the address
 * @ptr_f: The address of the pointer 
 * Return:Return 1 if freed up, otherwise 0.
 */
int bfree(void **ptr_f)
{
	if (ptr_f && *ptr_f)
	{
		free(*ptr_f);
		*ptr_f = NULL;
		return (1);
	}
	return (0);
}

