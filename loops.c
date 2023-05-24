#include "header.h"

/**
 * hsh - loop for main shell 
 * @inf: Struct parameter
 * @av: The argument vector from main() function
 *
 * Return: Return 0 on success, 1 on error
 */
int hsh(info_t *inf, char **av)
{
	ssize_t t = 0;
	int builtin_ret = 0;

	while (t != -1 && builtin_ret != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(inf);
		if (t != -1)
		{
			set_info(inf, av);
			builtin_ret = find_builtin(inf);
			if (builtin_ret == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (builtin_ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - Function will find builtin command
 * @inf: Struct parameter 
 *
 * Return: if -1  built-in not found,
 * 	if 0 built-in executed successfully,
 * 	if 1 built-in found but not successful,
 * 	if 2  built-in signals exit()
 */
int find_builtin(info_t *inf)
{
	int t, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (t = 0; builtintbl[t].type; t++)
		if (_strcmp(inf->argv[0], builtintbl[t].type) == 0)
		{
			inf->line_count++;
			built_in_ret = builtintbl[t].func(inf);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - Function will findsa command in the PATH
 * @info: Struct parameter
 * Return: void
 */
void find_cmd(info_t *inf)
{
	char *path = NULL;
	int t, x;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (t = 0, x = 0; inf->arg[t]; t++)
		if (!is_delim(inf->arg[t], " \t\n"))
			x++;
	if (!x)
		return;

	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
					|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "is not found\n");
		}
	}
}

/**
 * fork_cmd - Function will fork a exec thread to run cmd
 * @info: Struct parameter
 * Return: void
 */
void fork_cmd(info_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}

