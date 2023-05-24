#include "header.h"

/**
 * input_buf - function for buffer chained commands
 * @inf: Struct for parameter
 * @bufp: contain buffer
 * @ln: length var
 * Return: bytes
 */
ssize_t input_buf(info_t *inf, char **bufp, size_t *ln)
{
	ssize_t t = 0;
	size_t ln_p = 0;

	if (!*ln) 
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*bufp);
		*bufp = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(bufp, &ln_p, stdin);
#else
		t = _getline(inf, bufp, &ln_p);
#endif
		if (t > 0)
		{
			if ((*bufp)[t - 1] == '\n')
			{
				(*bufp)[t - 1] = '\0'; 
				t--;
			}
			inf->linecount_flag = 1;
			remove_comments(*bufp);
			build_history_list(inf, *bufp, inf->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*ln = t;
				inf->cmd_buf = bufp;
			}
		}
	}
	return (t);
}

/**
 * get_input - gets new line
 * @inf: Struct parameter
 * Return: bytes 
 */
ssize_t get_input(info_t *inf)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t t, x, ln;
	ssize_t r = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(inf, &buf, &ln);
	if (r == -1) /* EOF */
		return (-1);
	if (ln) /* we have commands left in the chain buffer */
	{
		x = t; /* init new iterator to current buf position */
		p = buf + t; /* get pointer for return */

		check_chain(inf, buf, &x, t, ln);
		while (x < ln) /* iterate to semicolon or end */
		{
			if (is_chain(inf, buf, &x))
				break;
			x++;
		}

		t = x + 1; /* increment past nulled ';'' */
		if (t >= ln) /* reached end of buffer? */
		{
			t = ln = 0; /* reset position and length */
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - Fucntion reads  buffers
 * @inf: Struct parameter
 * @bufp: contains buffer
 * @t: size
 * Return: j
 */
ssize_t read_buf(info_t *inf, char *bufp, size_t *t)
{
	ssize_t j = 0;

	if (*t)
		return (0);
	j = read(inf->readfd, bufp, READ_BUF_SIZE);
	if (j >= 0)
		*t = j;
	return (j);
}

/**
 * _getline - Function will get the next line from STDIN
 * @inf: Struct parameter
 * @xptr: address of pointer to buffer
 * @length: size of preallocated 
 * Return: e
 */
int _getline(info_t *inf, char **xptr, size_t *ln)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t j;
	ssize_t r = 0, e = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *xptr;
	if (p && ln)
		e = *ln;
	if (t == len)
		t = len = 0;

	r = read_buf(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + t, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, e, e ? e + j : j + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (e)
		_strncat(new_p, buf + t, j - t);
	else
		_strncpy(new_p, buf + t, j - t + 1);

	e += j - t;
	t = j;
	p = new_p;

	if (ln)
		*ln = e;
	*xptr = p;
	return (e);
}

/**
 * sigintHandler - Function will blocks ctrl-C
 * @sig_numb: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_numb)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

