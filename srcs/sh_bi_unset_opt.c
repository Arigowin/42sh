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

static int			unset_opt(char **arg, int fct, char opt, char **err_msg)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET OPT ------------------", 2);

	static char			oth_opt = '0';
	static int			ret = TRUE;
	int					i;

	i = 0;
	if (oth_opt == opt)
		return (ret);
	if (oth_opt == '0')
		oth_opt = opt;
	if (full_check_opt(arg, &oth_opt) == 2)
		return (2);
	while (arg[++i])
	{
		if (arg[i][0] != '-')
		{
			if ((ret = unset_check_env(arg[i], fct, FALSE)) == FALSE)
				ret = unset_check_env(arg[i], fct, TRUE);
			if (ret == ERROR)
				error_clear_str(ERROR, 34, arg[i], err_msg);
		}
	}
	return (ret);
}

int					unset_v(char **arg, char curr_opt, char *bi)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET V ------------------", 2);

	char				*err_msg;
	int					ret;

	(void)bi;
	err_msg = fill_tbl("unset -", curr_opt);
	ret = unset_opt(arg, FALSE, curr_opt, &err_msg);
	return (ret);
}

int					unset_f(char **arg, char curr_opt, char *bi)
{
	if (DEBUG_BI == 1)
		ft_putendl_fd("----------------------- UNSET F ------------------", 2);

	char				*err_msg;
	int					ret;

	(void)bi;
	err_msg = fill_tbl("unset -", curr_opt);
	ret = unset_opt(arg, TRUE, curr_opt, &err_msg);
	return (ret);
}
