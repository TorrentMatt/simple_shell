#include "header.h"

/**
 * get_history_file - Function will get the history file
 * @inf: Struct parameter
 * Return: Return string containg history file
 */

char *get_history_file(info_t *inf)
{
	char *buf, *dirx;

	dirx = _getenv(inf, "HOME=");
	if (!dirx)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dirx) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dirx);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Function will create  file, or appends to an existing file
 * @inf: Struct parameter
 * Return: Return 1 on success, else -1
 */
int write_history(info_t *inf)
{
	ssize_t fd;
	char *filename = get_history_file(inf);
	list_t *nde = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (nde = inf->history; nde; nde = nde->next)
	{
		_putsfd(nde->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - Function will read history from file
 * @inf: Struct parameter
 * Return: Return listcount on success, 0 otherwise
 */
int read_history(info_t *inf)
{
	int t, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (t = 0; t < fsize; t++)
		if (buf[t] == '\n')
		{
			buf[t] = 0;
			build_history_list(inf, buf + last, linecount++);
			last = t + 1;
		}
	if (last != t)
		build_history_list(inf, buf + last, linecount++);
	free(buf);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_history(inf);
	return (inf->histcount);
}

/**
 * build_history_list - Fuction wiil add entry to a history linked list
 * @inf: Struct parameter
 * @buf: buffer
 * @linecount: LINECOUNT
 * Return: Always 0
 */
int build_history_list(info_t *inf, char *buf, int linecount)
{
	list_t *nde = NULL;

	if (inf->history)
		nde = inf->history;
	add_node_end(&nde, buf, linecount);

	if (!inf->history)
		inf->history = nde;
	return (0);
}

/**
 * renumber_history - Function will re-number history linked list after changes
 * @inf: Struct parameter
 * Return:Return new listcount
 */
int renumber_history(info_t *inf)
{
	list_t *nde = inf->history;
	int t = 0;

	while (nde)
	{
		nde->num = t++;
		nde = nde->next;
	}
	return (inf->histcount = t);
}

