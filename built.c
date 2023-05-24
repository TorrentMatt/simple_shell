#include "header.h"

/**
 * _myexit - Function will exit the shell
 * @inf: Struct parameter
 * Return: Will exit with  given exit status
 */
int _myexit(info_t *inf)
{
	int exitck;

	if (inf->argv[1]) 
	{
		exitck = _erratoi(inf->argv[1]);
		if (exitck == -1)
		{
			inf->status = 2;
			print_error(inf, "number is illegal: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * _mycd - Function will change  current directory of the process in shell
 * @inf: Struct parameter
 * Return: 0
 */
int _mycd(info_t *inf)
{
	char *o, *dir, buffer[1024];
	int chdir_ret;

	o = getcwd(buffer, 1024);
	if (!o)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(o);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(inf, "Can not cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Fuction will change  current directory
 * @info: Struc parameter
 * Return: 0
 */
int _myhelp(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_puts("help call works. Function is not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

