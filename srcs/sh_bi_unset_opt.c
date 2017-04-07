#include "shell.h"
#include "libft.h"

static int			full_check_opt(char **arg, char *oth_opt)
{
	int					i;
	int					j;

	i = 0;
	while (arg && arg[++i] && arg[i][0] == '-')
	{
		j = -1;
		while (arg[i][++j])
		{
			if (arg[i][j] != '-' && arg[i][j] != *oth_opt)
			{
				*oth_opt = arg[i][j];
				return (2);
			}
		}
	}
	return (TRUE);
}

static int			unset_opt(char **arg, int fct, char opt, char *oth_opt)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET OPT ------------------", 2);

	static int			err_ret = FALSE;
	char				*err_msg;
	int					i;
	int					ret;

	i = 0;
	ret = TRUE;
	if (full_check_opt(arg, oth_opt) == 2)
		return (2);
	while (arg[++i])
	{
		if (arg[i][0] != '-')
		{
			if ((ret = unset_check_env(arg[i], fct, FALSE)) == FALSE)
				ret = unset_check_env(arg[i], fct, TRUE);
			if (ret == ERROR)
			{
				err_msg = fill_tbl("unset -", opt);
				err_ret = sh_error(err_ret, 34, arg[i], err_msg);
				ft_strdel(&err_msg);
				return (ERROR);
			}
		}
	}
	return (ret);
}

int					unset_v(char **arg, char curr_opt, char *bi)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET V ------------------", 2);

	static char			oth_opt = 'v';
	int 				fct;
	int					ret;

	(void)bi;
	if (oth_opt != 'v')
		return (2);
	fct = FALSE;
	ret = unset_opt(arg, fct, curr_opt, &oth_opt);
	return (ret);
}

int					unset_f(char **arg, char curr_opt, char *bi)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET F ------------------", 2);

	static char			oth_opt = 'f';
	int 				fct;
	int					ret;

	(void)bi;
	if (oth_opt != 'f')
		return (2);
	fct = TRUE;
	ret = unset_opt(arg, fct, curr_opt, &oth_opt);
	return (ret);
}
