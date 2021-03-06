/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:26:56 by dolewski          #+#    #+#             */
/*   Updated: 2017/04/13 18:15:23 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "shell.h"
#include "libft.h"

static char			*concat_to_str(char opt[3][2])
{
	char				*str;
	int					i;

	i = 0;
	if ((str = ft_strnew(4)) == NULL)
		sh_error(FALSE, 6, NULL, NULL);
	while (i < 3)
	{
		str[i] = opt[i][0];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int					bi_usage(char *bi, char curr_opt, char handled_opt[3][2])
{
	char				*str;

	str = concat_to_str(handled_opt);
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(bi, 2);
	ft_putstr_fd(": '", 2);
	ft_putchar_fd(curr_opt, 2);
	ft_putendl_fd("': invalid option", 2);
	ft_putstr_fd(bi, 2);
	ft_putstr_fd(": usage: ", 2);
	ft_putstr_fd(bi, 2);
	ft_putstr_fd(" [-", 2);
	ft_putstr_fd(str, 2);
	ft_strdel(&str);
	ft_putstr_fd("] [", 2);
	if (ft_strcmp(bi, "cd") == 0)
		ft_putstr_fd("dir", 2);
	if (ft_strcmp(bi, "env") == 0)
		ft_putstr_fd("exec", 2);
	if (ft_strcmp(bi, "export") == 0)
		ft_putstr_fd("name[=value] or export -p", 2);
	if (ft_strcmp(bi, "unset") == 0)
		ft_putstr_fd("name", 2);
	ft_putendl_fd("]", 2);
	return (str_dbltbl_ret(savior_fct_ret(39, TRUE), &str, NULL, NULL));
}

const char			*tbl_error1(int i)
{
	static const char	*err_tbl1[] = {"42sh: cannot access termacp database",
	"42sh: ioctl: cannot get window size", "42sh: cannot open ", "42sh: cannot \
open fd", "42sh: cannot performe pipe function", "42sh: cannot performe fork \
function", "42sh: memory allocation failed", "42sh: cannot duplicate fd",
	"42sh: bad file descriptor", "", "42sh: setenv: too many arguments",
	"42sh: cd: no OLDPWD variable set", "42sh: no PATH variable set", "42sh: \
cd: no HOME variable set", "", "42sh: setenv", "42sh: cd", "42sh", "42sh: \
parse error near", "42sh: exit", "42sh: warning: here-document was delimited \
by", "42sh: cannot performe stat function", "42sh: env: cannot specify '-0' \
with command", "42sh: export: no such variable", "42sh: line contains \
undefined character"};
	int					ret;

	ret = i;
	ret = (i >= 16 && i <= 18 ? 16 : ret);
	ret = (i == 26 ? 18 : ret);
	ret = (i == 9 || i == 15 || (i >= 19 && i <= 25) ||
	i == 29 || i == 14 || i == 30 || i == 33 || i == 34 ? 17 : ret);
	ret = (i >= 27 && i <= 28 ? 19 : ret);
	ret = (i == 31 ? 20 : ret);
	ret = (i == 32 ? 21 : ret);
	ret = (i == 35 ? 22 : ret);
	ret = (i == 36 ? 23 : ret);
	ret = (i == 37 ? 24 : ret);
	return (err_tbl1[ret]);
}

const char			*tbl_error2(int index)
{
	static const char	*err_tbl2[] = {": undefined variable",
	": not a valid identifier", ": not a directory",
	": no such file or directory", ": permission denied", ": invalid option",
	": command not found", ": value not set", ": too many arguments",
	": numeric argument required", ": bad file descriptor",
	": ambiguous redirect", ": is a directory", ": too few arguments",
	": bad environement variable type"};
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
	savior_fct_ret(index + 1, TRUE);
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
	if (index <= 7 || index == 23 || index == 24 || index == 32 || index == 37)
		exit_pgm(index);
	if (index == 26 || index == 34)
		return (NO_PRINT);
	return (ret);
}
