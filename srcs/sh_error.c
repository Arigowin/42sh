#include <string.h>
#include "shell.h"
#include "libft.h"

const char			*tbl_error1(int index)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- SH ERROR 1 ------------------", 2);

	static const char	*err_tbl1[] = {/*0*/"42sh: cannot access termacp database",
	/*1*/"42sh: ioctl: cannot get window size", /*2*/"42sh: cannot open ",
	/*3*/"42sh: cannot open fd", /*4*/"42sh: cannot performe pipe function",
	/*5*/"42sh: cannot performe fork function", /*6*/"42sh: memory allocation failed",
	/*7*/"42sh: cannot duplicate fd", /*8*/"42sh: bad file descriptor",/*9*/ "",
	/*10*/"42sh: setenv: too many arguments", /*11*/"42sh: cd: no OLDPWD variable set",
   	/*12*/"42sh: no PATH variable set", /*13*/"42sh: cd: no HOME variable set", /*14*/"",
   	/*15*/"42sh: setenv", /*16*/"42sh: cd", /*17*/"42sh", /*18*/"42sh: parse error near", /*19*/"42sh: exit",
	/*20*/"42sh: warning: here-document was delimited by",
	/*21*/"42sh: cannot performe stat function",
	/*22*/"42sh: env: cannot specify '-0' with command"};
	int					ret_index;

	ret_index = index;
	ret_index = (index >= 16 && index <= 18 ? 16 : ret_index);
	ret_index = (index == 26 ? 18 : ret_index);
	ret_index = (index == 9 || index == 15 || (index >= 19 && index <= 25) ||
	index == 29 || index == 14 || index == 30 || index == 33 || index == 34 ? 17 : ret_index);
	ret_index = (index >= 27 && index <= 28 ? 19 : ret_index);
	ret_index = (index == 31 ? 20 : ret_index);
	ret_index = (index == 32 ? 21 : ret_index);
	ret_index = (index == 35 ? 22 : ret_index);
	return (err_tbl1[ret_index]);
}

const char			*tbl_error2(int index)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- SH ERROR 2 ------------------", 2);

	static const char	*err_tbl2[] = {": undefined variable",
	": not a valid identifier", ": not a directory",
	": no such file or directory", ": permission denied", ": invalid option",
	": command not found", ": value not set", ": too many arguments",
	": numeric argument required", ": bad file descriptor",
	": ambiguous redirect", ": is a directory", ": too few arguments", ": bad environement variable type"};
	int					ret_index;

	ret_index = 0;
	ret_index = (index == 9 ? 13 : ret_index);
	ret_index = (index == 15 ? 1 : ret_index);
	ret_index = (index == 16 || index == 23 ? 2 : ret_index);
	ret_index = (index == 17 || index == 21 ? 3 : ret_index);
	ret_index = (index >= 18 && index <= 20 ? 4 : ret_index);
	ret_index = (index == 22 ? 5 : ret_index);
	ret_index = (index == 24 ? 6 : ret_index);
	ret_index = (index == 25 ? 7 : ret_index);
	ret_index = (index == 27 ? 8 : ret_index);
	ret_index = (index == 28 ? 9 : ret_index);
	ret_index = (index == 29 ? 10 : ret_index);
	ret_index = (index == 30 ? 11 : ret_index);
	ret_index = (index == 33 ? 12 : ret_index);
	ret_index = (index == 34 ? 14 : ret_index);
	return (err_tbl2[ret_index]);
}

int					sh_error(int ret, int index, char *err, char *bi)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- SH ERROR ------------------", 2);

	savior_pid(index, TRUE);
	if (ret == NO_PRINT)
		return (NO_PRINT);
	ft_putstr_fd(tbl_error1(index), 2);
	if (bi != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(bi, 2);
	}
	if (err != NULL)
	{
		ft_putstr_fd(": '", 2);
		ft_putstr_print_fd(err, 2);
		ft_putstr_fd("'", 2);
	}
	if (index == 9 || (index >= 14 && index <= 34 && index != 26 && index != 32
	&& index != 31))
		ft_putstr_fd(tbl_error2(index), 2);
	ft_putendl_fd("", 2);
	if (index <= 7 || index == 23 || index == 24 || index == 32)
		exit_pgm(EXIT_FAILURE);
	if (index == 26 || index == 34)
		return (NO_PRINT);
	return (ret);
}
