#include "header.h"

/**
 * is_cmd - Function will  determine if file is  executabl
 * @inf: Struct parameter
 * @pth: Path
 *
 * Return: Return 1 if true, 0 otherwise
 */
int is_cmd(info_t *inf, char *pth)
{
	struct stat st;

	(void)inf;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Fuction will duplicates characters
 * @pthstr: PATH string
 * @start_i: starting index
 * @stop: stopping index
 *
 * Return: Retrun pointer to new buffer
 */
char *dup_chars(char *pthstr, int start_i, int stop)
{
	static char buf[1024];
	int t = 0, k = 0;

	for (k = 0, t = start_i; t < stop; t++)
		if (pthstr[t] != ':')
			buf[k++] = pthstr[t];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Fuction wil find cmd in the PATH string
 * @inf: Struct parameter
 * @pathstr: PATH string
 * @cmd: cmd
 * Return: Return full path of cmd if found
 */
char *find_path(info_t *inf, char *pathstr, char *cmd)
{
	int t = 0, curr_pos = 0;
	char *pth;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[t] || pathstr[t] == ':')
		{
			pth = dup_chars(pathstr, curr_pos, t);
			if (!*pth)
				_strcat(pth, cmd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmd);
			}
			if (is_cmd(inf, pth))
				return (pth);
			if (!pathstr[t])
				break;
			curr_pos = t;
		}
		t++;
	}
	return (NULL);
}

